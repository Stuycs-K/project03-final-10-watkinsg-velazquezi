#include "networking.h"

void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}

int server_setup() {
  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1, sizeof(struct addrinfo)); // error in vscode for this..??
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, PORT, hints, &results);

  //create the socket
  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
	
  //this code should get around the address in use error
  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt error");

  //bind the socket to address and port
  bind(clientd, results->ai_addr, results->ai_addrlen);
  
  //set socket to listen state
  listen(clientd, 100);

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  
  return clientd;
}