#include "networking.h"

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup();
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  fd_set read_fds;
  while (1) {
      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);
      // ???
      // figure out how to continually listen to clients while also having an initial 'lobby' before sending task packets out
  }
}
