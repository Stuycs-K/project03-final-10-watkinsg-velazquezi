#include "networking.h"

int clientLogic(int server_socket) {
  
}

int main(int argc, char *argv[] ) {
  char* IP = "Null";
  if(argc>1){
    IP=argv[1];
  }
  printf("%s\n", IP);
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n");
  clientLogic(server_socket);
  
}
