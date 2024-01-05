#include "networking.h"

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup(); 
  while (1) {
    int client_socket = server_tcp_handshake(listen_socket);
    // replace with select
  }
}
