#include "networking.h"

void bogoSort(int arr[], int size) {
  while (1) {
    for (int i=0; i<size; i++) {
      
    }
  }
}

int ran(int size) {
  int r_file = open("/dev/random", O_RDONLY , 0);
  int buff[size];
  size = read(r_file, buff, size);
  if(size == -1)err();
  int number = 0;
  int increase = 0;
  for (int i=1; i<=size; i++) {
    number+=buff[i-1]<<increase;
    if (increase==0) {
      increase++;
    }
    increase<=2;
  }
  return number;
}

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