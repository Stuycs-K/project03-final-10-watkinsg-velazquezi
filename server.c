#include "networking.h"
// TODO: start in a 'lobby' mode that doesn't send/recieve data to clients - only connects
// when reading from stdin check if the command is 'start', if so, set a bool to true and send tasks to client (then start reading)

static int sign = 0;

static void sighandler( int signo ) {
    
    if (signo==SIGINT) {
      sign = 1;
    }
    if (signo==SIGQUIT) {
      sign = -1;
    }
}

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup();

  signal(SIGQUIT, &sighandler);
  signal(SIGINT, &sighandler);
  
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
    struct timeval timeout = { 1, 0 };
    select(listen_socket+1, &read_fds, NULL, NULL, NULL);

    // if not started, check for new clients
    if (started == 0 && FD_ISSET(listen_socket, &read_fds)) {
      int client_socket = server_tcp_handshake(listen_socket);
      printf("client connected.\n");
      FD_SET(client_socket, &read_fds);
      printf("past client fdset\n");
      // add client socket to array (first open spot? find it?)
    }
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      printf("stdin is set!!\n");
      char input[100];
      fgets(input, sizeof(input), stdin); // use read()?
      printf("input: %s\n", input);
      // handle commands such as:
      // status - prints an overview of the current state including clients, etc
      // start - starts the project, sends tasks to clients
      // stop - stops the project, sends stop p staacket to clients
      // kill - ends every client process and stops the server
    }
    // for every client descriptor stored, check if it has data to read
    int SIZEOF = 10;
    for (int i = 0; i < SIZEOF; i++) {
      if (FD_ISSET(cli_socks[i], &read_fds)) {
        // check if client disconnected (read() returns 0), if so then remove from array with remove()
        if (sign==-1 || 1/* INSERT CONDITION FOR DISCONNECT */) {
          removeIndex(cli_socks, 10, i);
          i--;
          SIZEOF--;
          /*
            Whatever the send method is goes here to send packets to KILL
          */

        } 
        else if (sign==1) {
          /*
            Whatever the send method is goes here to send packets to STOP
          */
        }
        else {
          subserver_logic(cli_socks[i]);
        }
      }
    }   
    if (sign==-1) {
      exit(0);
    }

      // ???
      // figure out how to continually listen to clients while also having an initial 'lobby' before sending task packets out
  }
}
