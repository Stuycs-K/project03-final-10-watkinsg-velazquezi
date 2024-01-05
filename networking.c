#include "networking.h"

void copyArr(int dest[], int copying[], int size) {
  for (int i=0; i<size; i++) {
    dest[i] = copying[i];
  }
}

void bogoSort(int arr[], int size) {
  while (1) {
    for (int i=0; i<size; i++) {
      
    }
  }
}

void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}

int ran(int size) {
  int r_file = open("/dev/random", O_RDONLY , 0);
  int buff[size];
  size = read(r_file, buff, size);
  err(size, "file not found");
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

int client_tcp_handshake(char * server_address) {

  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  if (!strcmp(server_address, "Null")) {
    getaddrinfo(NULL, PORT, hints, &results);
  }
  else {
    getaddrinfo(server_address, PORT, hints, &results);
  }
    //Server sets node to NULL

  //getaddrinfo
  
  int sd = socket(results->ai_family, results->ai_socktype, 0);
  //create the socket
  connect(sd, results->ai_addr, results->ai_addrlen);
  //connect to the server
  
  free(hints);
  freeaddrinfo(results);

  return sd;
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
  listen(clientd, 10);

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  
  return clientd;
}

int clientLogic(int server_socket) {
  struct packet *data = malloc(sizeof(struct packet));
  int bytes = read(server_socket, data, sizeof(struct packet));
  err(bytes, "Server error");
  int type = data->type;
  int arr[10];
  copyArr(arr, data->arr, 10);
  int seeds[10];
  copyArr(seeds, data->seeds, 10);
  while (1) {
    read(server_socket, data, sizeof(struct packet));
    if (type==-1) {
      close(server_socket);
      exit(0);
    }
  }
}

int subserver_logic(int client_socket) {

}

int server_tcp_handshake(int listen_socket) {
  
}