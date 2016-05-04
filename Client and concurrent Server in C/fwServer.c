/***************************************************************************
 *            fwServer.c
 *
 *  Copyright  2016  mc
 *  <mc@<host>>
 ****************************************************************************/

#include "fwServer.h"

/**
 * Returns the port specified as an application parameter or the default port
 * if no port has been specified.
 * @param argc the number of the application arguments.
 * @param an array with all the application arguments.
 * @return  the port number from the command line or the default port if
 * no port has been specified in the command line. Returns -1 if the application
 * has been called with the wrong parameters.
 */
int getPort(int argc, char* argv[])
{
  int param;
  int port = DEFAULT_PORT;

  optind = 1;
  // We process the application execution parameters.
	while((param = getopt(argc, argv, "p:")) != -1){
		switch((char) param){
			case 'p':
			  // We modify the port variable just in case a port is passed as a
			  // parameter
				port = atoi(optarg);
				break;
			default:
				printf("Parametre %c desconegut\n\n", (char) param);
				port = -1;
		}
	}

	return port;
}


 /**
 * Function that sends a HELLO_RP to the  client
 * @param sock the communications socket
 */
void process_HELLO_msg(int sock)
{
  char buffer[MAX_BUFF_SIZE];
  unsigned short opcode_response = MSG_HELLO_RP;
  opcode_response = htons(opcode_response);

  struct hello_rp hello;
  hello.opcode = opcode_response;
  strcpy(hello.msg, "Hello World0");

  *((struct hello_rp*)buffer) = hello;

	send(sock, buffer, sizeof(hello),0);
}

/**
* Process the list petition from the client.
* Sends the list of firewall rules to the client
* @param sock the communications socket
* @param chain the chain with the filer rules
*/
void process_list_msg(int sock, struct FORWARD_chain *chain, char * buffer)
{

  unsigned short opcode_response = MSG_RULES;

  int offset = 0;
  stshort(opcode_response, buffer);
  offset += sizeof(short);

  stshort(chain->num_rules, &buffer[offset]);
  offset += sizeof(short);

  struct FORWARD_rule ruleToSend;

  if(chain->num_rules != 0)
  {
    int i;
    struct fw_rule * iter;
    iter = chain->first_rule;
    for (i = 0; i < chain->num_rules; i++){
      ruleToSend.mask = htons(iter->rule.mask);
      ruleToSend.port = htons(iter->rule.port);
      ruleToSend.src_dst_addr = htons(iter->rule.src_dst_addr);
      ruleToSend.src_dst_port = htons(iter->rule.src_dst_port);
      ruleToSend.addr = iter->rule.addr;
      (*((struct FORWARD_rule *)&buffer[offset])) = ruleToSend;
      offset += sizeof(struct FORWARD_rule);
      iter = iter->next_rule;

    }
  }

  send(sock, buffer, offset,0);

}

/**
 * Stores the rule sent by the client in the list of rules
 * @param sock the communications socket
 * @param chain the chain with the filer rules
 * @param buffer buffer containing the request sent by the user
 */
 void process_add_msg(int sock, struct FORWARD_chain * chain, char * buffer)
 {
  int offset = sizeof(unsigned short);
  struct FORWARD_rule received_rule = (*(struct FORWARD_rule *)&buffer[offset]);

  received_rule.mask = ntohs(received_rule.mask);
  received_rule.port = ntohs(received_rule.port);
  received_rule.src_dst_addr = ntohs(received_rule.src_dst_addr);
  received_rule.src_dst_port = ntohs(received_rule.src_dst_port);

  struct fw_rule * new_rule = malloc(sizeof(struct fw_rule));
  new_rule->rule = received_rule;
  new_rule->next_rule = NULL;

  if (chain->num_rules == 0){
    chain->first_rule = new_rule;
  }
  else{
    int i;
    struct fw_rule * iter;
    iter = chain->first_rule;

    for(i = 0; i < chain->num_rules-1; i++){
      iter = iter->next_rule;
    }

    iter->next_rule = new_rule;

  }
  chain->num_rules = chain->num_rules + 1;


 }

 /**
  * Changes the rule indicated to the new rule sent in the request
  * @param sock the communications socket
  * @param chain the chain with the filer rules
  * @param buffer buffer containing the request sent by the user
  */
  void process_change_msg(int sock, struct FORWARD_chain * chain, char * buffer)
  {
    int offset = sizeof(unsigned short);
    unsigned short id = ldshort(&buffer[offset]);
    offset += sizeof(unsigned short);

    unsigned short opcode;

    if (id <= (chain->num_rules)){
      struct FORWARD_rule received_rule = (*(struct FORWARD_rule *)&buffer[offset]);
      received_rule.mask = ntohs(received_rule.mask);
      received_rule.port = ntohs(received_rule.port);
      received_rule.src_dst_addr = ntohs(received_rule.src_dst_addr);
      received_rule.src_dst_port = ntohs(received_rule.src_dst_port);

      int i;
      struct fw_rule * iter;
      iter = chain->first_rule;
      for (i = 0; i < id - 1; i++)
      {
        iter = iter->next_rule;
      }

      iter->rule = received_rule;

      opcode = MSG_OK;

    }else{
      opcode = MSG_ERR;
    }

    memset(buffer, '\0', sizeof(buffer));
    stshort(opcode, buffer);
    send(sock, buffer, sizeof(short),0);

  }

 /**
 * Receives and process the request from a client.
 * @param the socket connected to the client.
 * @param chain the chain with the filter rules.
 * @return 1 if the user has exit the client application therefore the
 * connection whith the client has to be closed. 0 if the user is still
 * interacting with the client application.
 */
int process_msg(int sock, struct FORWARD_chain *chain)
{
  int finish = 0;
  char buffer[MAX_BUFF_SIZE];
  unsigned short op_code;
  recv(sock, buffer, sizeof(buffer), 0);
  op_code = ldshort(buffer);

  switch(op_code)
  {
    case MSG_HELLO:
      process_HELLO_msg(sock);
      break;
    case MSG_LIST:
      process_list_msg(sock, chain, buffer);
      break;
    case MSG_ADD:
      process_add_msg(sock,chain, buffer);
      break;
    case MSG_CHANGE:
      process_change_msg(sock,chain, buffer);
      break;
    case MSG_DELETE:
      break;
    case MSG_FLUSH:
      break;
    case MSG_FINISH:
      finish = 1;
      break;
    default:
      perror("Message code does not exist.\n");
  }

  return finish;
}

int main(int argc, char *argv[]){
  int port = getPort(argc, argv);
  int finish = 0;
  int s, s2;
  struct FORWARD_chain chain;

  chain.num_rules = 0;
  chain.first_rule = NULL;

  // Info del socket guardada en una struct sockaddr_in
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  struct sockaddr_in client_addr;
  socklen_t client_addrlen = sizeof(client_addr);

  // System call socket
	s = socket(PF_INET, SOCK_STREAM, 0);

  // Bind: associar adrça al socket;
  bind(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
  listen(s, MAX_QUEUED_CON);
  int pid;
  while(1)
  {
    s2 = accept(s, (struct sockaddr *)&client_addr,&client_addrlen);
    pid = fork();

   if(pid == -1){
      perror("Error en el fork");
      exit(EXIT_FAILURE);
    }
     if(pid == 0){
       do {
         finish = process_msg(s2, &chain);
       }while(!finish);
       close(s2);
       exit(EXIT_SUCCESS);
     }
   }

  return 0;
 }
