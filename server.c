#include "networking.h"
// TODO: start in a 'lobby' mode that doesn't send/recieve data to clients - only connects
// when reading from stdin check if the command is 'start', if so, set a bool to true and send tasks to client (then start reading)
int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup();

  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  fd_set read_fds;
  int cli_socks[MAX_CLIENTS] = {0}; // make the max number of clients a macro?

  FD_ZERO(&read_fds);
  
  FD_SET(STDIN_FILENO, &read_fds);
  FD_SET(listen_socket, &read_fds);

  int started = -1; // 0 = false, 1 = true

  while (1) {
    char input[100];
    if (started==-1) {
      printf("Press enter to begin\n");
      read(STDIN_FILENO, input, 100);
      input[0];
      started = 0;
    }
    
    select(listen_socket+1, &read_fds, NULL, NULL, NULL);

    

    // if not started, check for new clients
    if (started == 1 && FD_ISSET(listen_socket, &read_fds)) {
      int client_socket = server_tcp_handshake(listen_socket);
      printf("client connected.\n");
      FD_SET(client_socket, &read_fds);
      // add client socket to array (first open spot? find it?)
    }
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      
      started = 0;
      fflush(stdout);
      fgets(input, sizeof(input), stdin); // use read()?
      printf("input: %s\n", input);
      // handle commands such as:
      // status - prints an overview of the current state including clients, etc
      // start - starts the project, sends tasks to clients
      // stop - stops the project, sends stop packet to clients
      // kill - ends every client process and stops the server
    }
    // for every client descriptor stored, check if it has data to read
    for (int i = 0; i < 10; i++) {
      if (FD_ISSET(cli_socks[i], &read_fds)) {
        // check if client disconnected (read() returns 0), if so then remove from array with remove()
        if (1/* INSERT CONDITION FOR DISCONNECT */) {
          removeIndex(cli_socks, 10, i);
        } else {
          subserver_logic(cli_socks[i]);
        }
      }
    }

    

      // ???
      // figure out how to continually listen to clients while also having an initial 'lobby' before sending task packets out
  }
}
