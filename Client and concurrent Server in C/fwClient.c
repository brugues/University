/***************************************************************************
 *            fwClient.h
 *
 *  Copyright  2016  mc
 *  <mcarmen@<host>>
 ****************************************************************************/
#include "fwClient.h"

/**
 * Function that sets the field addr->sin_addr.s_addr from a host name
 * address.
 * @param addr struct where to set the address.
 * @param host the host name to be converted
 * @return -1 if there has been a problem during the conversion process.
 */
int setaddrbyname(struct sockaddr_in *addr, char *host)
{
  struct addrinfo hints, *res;
	int status;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(host, NULL, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return -1;
  }

  addr->sin_addr.s_addr = ((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr;

  freeaddrinfo(res);

  return 0;
}


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

  optind=1;
  // We process the application execution parameters.
	while((param = getopt(argc, argv, "h:p:")) != -1){
		switch((char) param){
		  case 'h': break;
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
 * Returns the host name where the server is running.
 * @param argc the number of the application arguments.
 * @param an array with all the application arguments.
 * @Return Returns the host name where the server is running.<br />
 * Returns null if the application has been called with the wrong parameters.
 */
 char * getHost(int argc, char* argv[]){
  char * hostName = NULL;
  int param;

  optind=1;
    // We process the application execution parameters.
	while((param = getopt(argc, argv, "h:p:")) != -1){
		switch((char) param){
			case 'p': break;
			case 'h':
        hostName = (char*) malloc(sizeof(char)*strlen(optarg)+1);
				// Un cop creat l'espai, podem copiar la cadena
				strcpy(hostName, optarg);
				break;
			default:
				printf("Parametre %c desconegut\n\n", (char) param);
				hostName = NULL;
		}
	}

	printf("in getHost host: %s\n", hostName); //!!!!!!!!!!!!!!
	return hostName;
 }



/**
 * Shows the menu options.
 */
void print_menu()
{
		// Mostrem un menu perque l'usuari pugui triar quina opcio fer

		printf("\nAplicació de gestió del firewall\n");
		printf("  0. Hello\n");
		printf("  1. Llistar les regles filtrat\n");
		printf("  2. Afegir una regla de filtrat\n");
		printf("  3. Modificar una regla de filtrat\n");
		printf("  4. Eliminar una regla de filtrat\n");
		printf("  5. Eliminar totes les regles de filtrat.\n");
		printf("  6. Sortir\n\n");
		printf("Escull una opcio: ");
}


/**
 * Sends a HELLO message and prints the server response.
 * @param sock socket used for the communication.
 */
void process_hello_operation(int sock)
{
  char buffer[MAX_BUFF_SIZE];
  unsigned short code = MSG_HELLO;
  stshort(code, buffer);

  send(sock, buffer, sizeof(short), 0);



  memset(buffer, '\0', sizeof(buffer)); //Inicialitzar el buffer tot a zeros

  recv(sock, &buffer, sizeof(buffer), 0);


  struct hello_rp received = *((struct hello_rp *)buffer);

  int i = 0;
  while((i<sizeof(received.msg))&&(received.msg[i] != '0')){
    printf("%c", received.msg[i]);
    i = i + 1;
  }
  printf("\n");
}

/**
 * Closes the socket connected to the server and finishes the program.
 * @param sock socket used for the communication.
 */
void process_exit_operation(int sock)
{
  char buffer[MAX_BUFF_SIZE];
  unsigned short code = MSG_FINISH;
  stshort(code, buffer);

  send(sock, buffer, sizeof(short), 0);

  close(sock);
  exit(0);
}

/*
 * Sends a list request to the server defined by code 3
 * Then receives and prints the response of the server with the list of rules
 * @param sock socket used for the communication.
 */
void process_list_operation(int sock)
{
  char buffer[MAX_BUFF_SIZE];
  short code = MSG_LIST;
  stshort(code, buffer);

  send(sock, buffer, sizeof(short), 0);

  recv(sock, &buffer, sizeof(buffer), 0);


  int offset = 0;
  code = ldshort(buffer);
  offset += sizeof(short);

  short num_rules = ldshort(&buffer[offset]);
  offset += sizeof(short);


  printf("\nRegles de FORWARD: \n");
  struct FORWARD_rule rule;
  char * address;
  char src_dst_port [5];
  char src_dst_addr [3];
  int i;
  for (i = 0; i < num_rules; i++)
  {
    rule = (*((struct FORWARD_rule *)(&buffer[offset])));
    offset += sizeof(struct FORWARD_rule);

    address = inet_ntoa(rule.addr);
    rule.mask = ntohs(rule.mask);
    rule.port = ntohs(rule.port);
    rule.src_dst_addr = ntohs(rule.src_dst_addr);
    rule.src_dst_port = ntohs(rule.src_dst_port);
    if(rule.src_dst_addr == SRC){
      strcpy(src_dst_addr, "src");
    }else{
      strcpy(src_dst_addr, "dst");
    }

    if(rule.src_dst_port == SRC){
      strcpy(src_dst_port, "sport");
    }else{
      strcpy(src_dst_port, "dport");
    }
    printf("%i %s %s/%u %s %u\n",(i+1),src_dst_addr, address,rule.mask,src_dst_port, rule.port);
  }
}

/*
 * Adds a rule to the server list of rules
 * Asks the user to introudce the fields of a rule and sends the rule to the server
 * @param sock socket used for the communication.
 */
void process_add_operation(int sock)
{
  char buffer[MAX_BUFF_SIZE];
  unsigned short code = MSG_ADD;

  printf("Introdueix la regla seguint el seguent format: \n src|dst address Netmask [sport|dport] [port]\n\n");

  char opc[3];
  char address[15];
  char portSelector[5];
  unsigned short mask;
  unsigned short port;
  char src[3];
  strcpy(src, "src");
  char sport[5];
  strcpy(sport, "sport");
  struct FORWARD_rule rule;

  scanf("%s %s %hu %s %hu", opc, address, &mask, portSelector, &port);

  rule.mask = htons(mask);
  rule.port = htons(port);


  if (strcmp(opc, src) == 0){
    rule.src_dst_addr = htons(SRC);
  }else{
    rule.src_dst_addr = htons(DST);
  }

  if(strcmp(portSelector, sport) == 0){
    rule.src_dst_port = htons(SRC);
  }else{
    rule.src_dst_port = htons(DST);
  }

  //Convert the address from dotted quad format to be sent to the network
  inet_aton(address, &rule.addr);

  int offset = 0;
  stshort(code,buffer);
  offset += sizeof(unsigned short);

  (*((struct FORWARD_rule *)&buffer[offset]) = rule);
  offset += sizeof(struct FORWARD_rule);



  send(sock, buffer, offset, 0);

  process_list_operation(sock);
}


/*
 * Changes the rule of the server according to user input
 * Asks the user to introduce the new rule to be added
 * @param sock socket used for the communication.
 */
void process_change_operation(int sock)
{
unsigned short opcode = MSG_CHANGE;

  process_list_operation(sock);
  printf("Indica l’identificador de la regla a modificar seguint el format:\n rule_id src|dst address Netmask [sport|dport] [port] \n");

  unsigned short id;
  char opc[3];
  char address[15];
  char portSelector[5];
  unsigned short mask;
  unsigned short port;
  char src[3];
  strcpy(src, "src");
  char sport[5];
  strcpy(sport, "sport");
  struct FORWARD_rule rule;

  scanf("%hu %s %s %hu %s %hu",&id, opc, address, &mask, portSelector, &port);

  rule.mask = ntohs(mask);
  rule.port = ntohs(port);

  if (strcmp(opc, src) == 0){
    rule.src_dst_addr = htons(SRC);
  }else{
    rule.src_dst_addr = htons(DST);
  }

if(strcmp(portSelector, sport) == 0){
    rule.src_dst_port = htons(SRC);
  }else{
    rule.src_dst_port = htons(DST);
  }

  inet_aton(address, &rule.addr);

  char buffer[MAX_BUFF_SIZE];
  int offset = 0;
  stshort(opcode, buffer);
  offset += sizeof(short);
  stshort(id, &buffer[offset]);
  offset += sizeof(short);

  (*((struct FORWARD_rule *)&buffer[offset]) = rule);
  offset += sizeof(struct FORWARD_rule);

  send(sock, buffer, offset, 0);

  recv(sock, &buffer, sizeof(buffer), 0);

  opcode = ldshort(buffer);
  if(opcode == MSG_OK){
    printf("\nLa regla s'ha modificat amb exit\n");
    process_list_operation(sock);
  }else{
    printf("La regla no existeix\n");
  }
}


/**
* Function that asks the server to delete one firewall rule,
* which is indicated in the message that is send.
* @param sock the communication socket
*/
void process_delete_operation(int sock)
{
  char buffer[MAX_BUFF_SIZE];
  unsigned short code = MSG_DELETE;
  stshort(code, buffer);

  unsigned short id;
  printf("Indica l'ID de la norma que vulguis eliminar del firewall");
  scanf("%hu", &id);

  (*((short *)&buffer[sizeof(short)]) = id);

  send(sock, buffer, 2*sizeof(short));

  process_list_operation(sock);
}

/**
* Function that asks the server to delete all the firewall rules
* @param sock the communication socket
*/
void process_flush_operation(int sock)
{
  char buffer[MAX_BUFF_SIZE];
  unsigned short code = MSG_FLUSH;
  stshort(code, buffer);

  send(sock, buffer, sizeof(short), 0);

  process_list_operation(sock);
}

/**
 * Function that process the menu option set by the user by calling
 * the function related to the menu option.
 * @param s The communications socket
 * @param option the menu option specified by the user.
 */
void process_menu_option(int s, int option)
{
  switch(option){
    // Opció HELLO
    case MENU_OP_HELLO:
      process_hello_operation(s);
      break;
    case MENU_OP_LIST_RULES:
      process_list_operation(s);
      break;
    case MENU_OP_ADD_RULE:
      process_add_operation(s);
      break;
    case MENU_OP_CHANGE_RULE:
      process_change_operation(s);
      break;
    case MENU_OP_DEL_RULE:
      process_delete_operation(s);
      break;
    case MENU_OP_FLUSH:
      process_flush_operation(s);
      break;
    case MENU_OP_EXIT:
      process_exit_operation(s);
      break;
    default:
      printf("Invalid menu option\n");
  }
}


int main(int argc, char *argv[]){
  int s;
  unsigned short int port;
  char *hostName;
  int menu_option = 0;
  port = getPort(argc, argv);
  hostName = getHost(argc, argv);

  //Checking that the host name has been set.Otherwise the application is stopped.
	if(hostName == NULL){
		perror("No s'ha especificat el nom del servidor\n\n");
		return -1;
	}

  // System call socket
	s = socket(PF_INET, SOCK_STREAM, 0);

  // Info del socket guardada en una struct sockaddr_in
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  setaddrbyname(&server_address, hostName);

  connect(s, (struct sockaddr*)&server_address, sizeof(struct sockaddr));

  do{
      print_menu();
		  // getting the user input.
		  scanf("%d",&menu_option);
		  printf("\n\n");
		  process_menu_option(s, menu_option);
	  }while(menu_option != MENU_OP_EXIT); //end while(opcio)

  return 0;
}
