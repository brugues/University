#include "Socket.h"

#include <string.h>
#include <strings.h>
#include <stdio.h>
#define MAXBUFSIZE 10000

Socket::Socket(char *hostname, int port, int tcp) {
  host = hostname;
  host_id = gethostbyname(host);
  // open socket
  server_addr.sin_family = AF_INET;      /* host byte order */
  server_addr.sin_port = htons(port);    /* short, network byte order */
  server_addr.sin_addr = *((struct in_addr *)host_id->h_addr);
  bzero(&(server_addr.sin_zero), 8);     /* zero the rest of the struct */
  if (tcp) { // TCP
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      printf("Error: tcp socket could not be opened\n");
    } else {
      if (connect(sock, (struct sockaddr *)&server_addr,
		  sizeof(struct sockaddr)) == -1) {
	printf("Error: tcp socket could not connect\n");    
      }
    }
  } else { // UDP
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
      printf("Error: udp socket could not be opened\n");
    } else {
      if (connect(sock, (struct sockaddr *)&server_addr,
		  sizeof(struct sockaddr)) == -1) {
	printf("Error: udp socket could not connect\n");    
      }
    }
  }
}

char *Socket::read(int cnt) {
  static char buf[MAXBUFSIZE];
  char ch[5];
  bzero(buf, MAXBUFSIZE);
  int numbytes;
  for (int i = 0; i < cnt; i++) {
    numbytes = recv(sock, ch, 1, 0);
    if (numbytes == 1) {
      //printf("%d ", (int)ch[0]);
      buf[i] = ch[0];
    } else {
      i--;
    }
  }
  //printf("\nread %d bytes: ", cnt);
  return buf;
}

int Socket::write(char *message) {
  return send(sock, message, strlen(message), 0);
}

char *Socket::readUntil(char stop) {
  static char retval[MAXBUFSIZE];
  int numbytes = 0;
  char ch[5];
  int pos = 0;
  numbytes = recv(sock, &ch, 1, 0);
  while (ch[0] != stop && numbytes == 1 && pos < 50) { // no text is > 50
    retval[pos++] = ch[0];
    numbytes = recv(sock, &ch, 1, 0);
  }
  retval[pos] = 0; // end of string
  //printf("readUntil: read %d chars\n", pos);
  return retval;
}


