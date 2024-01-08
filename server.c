#include "networking.h"

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup();
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  fd_set read_fds;
  FD_ZERO(&read_fds);
  FD_SET(STDIN_FILENO, &read_fds);
  FD_SET(listen_socket, &read_fds);
  while (1) {
    select(listen_socket+1, &read_fds, NULL, NULL, NULL);
    if (FD_ISSET(listen_socket, &read_fds)) {
      int client_socket = server_tcp_handshake(listen_socket);
      printf("client connected.\n");
      FD_SET(client_socket, &read_fds);
    }
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      char input[100];
      fgets(input, sizeof(input), stdin); // use read()?
      printf("input: %s\n", input);
    }

      // ???
      // figure out how to continually listen to clients while also having an initial 'lobby' before sending task packets out
  }
}
