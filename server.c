#include "util.h"
// TODO: start in a 'lobby' mode that doesn't send/recieve data to clients - only connects
// when reading from stdin check if the command is 'start', if so, set a bool to true and send tasks to client (then start reading)

static int sign = 0;

// static void sighandler( int signo ) {
    
//   if (signo==SIGQUIT) {
//     sign = 1;
//   }
//   if (signo==SIGINT) {
//     sign = -1;
//   }
  
// }

/*
  what does server do?
  {
    listen - once
    while (1) {
      if (connect) {
        accept
      }
      if (terminal) {
        smthn, but not rn
        if (stop) {
          write stop
        }
      }
      for (int i=0; i<MAX_CLIENTS; i++) {
        else {
          write request
          read the request
        }
      }
    }
  }
*/

int main(int argc, char *argv[] ) {
  // setvbuf(stdout, NULL, _IONBF, 0);

  int listen_socket = server_setup();
  // signal(SIGQUIT, &sighandler);
  // signal(SIGINT, &sighandler);
  
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  fd_set read_fds;
  int cli_socks[MAX_CLIENTS] = {0}; // make the max number of clients a macro?

  FD_ZERO(&read_fds);
  

  int started = 0; // 0 = false, 1 = true

  while (1) {
    printf("Please send a message: \n");
    int highestClient = findHighest(cli_socks, MAX_CLIENTS);
    int highestDescriptor = highestClient > listen_socket ? highestClient : listen_socket;
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(listen_socket, &read_fds);
    select(highestDescriptor+1, &read_fds, NULL, NULL, NULL);

    // if not started, check for new clients
    if (started == 0 && FD_ISSET(listen_socket, &read_fds)) {
      int client_socket = server_tcp_handshake(listen_socket);
      printf("client connected.\n");
      FD_SET(client_socket, &read_fds);
      printf("past client fdset\n");
      appendArr(cli_socks, client_socket);
      printf("first thing in cli_socks is %d\n", cli_socks[0]);
      continue;
    }
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      char input[100];
      fgets(input, sizeof(input), stdin); // use read()?
      printf("input: %s\n", input);
      // handle commands such as:
      // status - prints an overview of the current state including clients, etc
      // start - starts the project, sends tasks to clients
      if (!strcmp(input, "start\n")) {
        printf("in\n");
        started = 1;
        int numclients = 0;
        numclients = amountOfClients(cli_socks);
        int seedsperclient = TOTAL_SEEDS / numclients;
        printf("%d clients with %d seeds each (out of %d)\n", numclients, seedsperclient, TOTAL_SEEDS);

        
        int extra = TOTAL_SEEDS % numclients;
        for (int i = 0; i < numclients; i++) {
          struct packet *data = malloc(sizeof(struct packet));
          data->type = PACKET_REQUEST;
          int seeds[PACKET_SEEDS] = {0};
          for (int j = seedsperclient * i + extra; j < seedsperclient * (i + 1) + extra; j++) {
            appendArr(seeds, j);
          }
          copyArr(data->seeds, seeds, PACKET_SEEDS);
          write(cli_socks[i], data, sizeof(struct packet));
          // TODO: handle extra seeds
          // if (i = 0) {
          //   j -= extra;
          //   for (int j = 0; j < extra; j++) {
          //     appendArr()
          //   }
          // }
          printf("Sent tasks to clients!\n");

        }
      }
      else if (!strcmp(input, "display\n")) {
          int numclients = amountOfClients(cli_socks);
          for (int i=0; i<numclients; i++) {
            subserver_logic(cli_socks[i]);
          }
      }
      // stop - stops the project, sends stop p staacket to clients
      // kill - ends every client process and stops the \server
      continue;
    }
    // for every client descriptor stored, check if it has data to read
    int SIZEOF = 10;
    for (int i = 0; i < SIZEOF; i++) {
      if (FD_ISSET(cli_socks[i], &read_fds) && cli_socks[i] != 0) {
        printf("Client socket %d has data ready??\n", i);
        // check if client disconnected (read() returns 0), if so then remove from array with remove()
        struct packet *data = malloc(sizeof(struct packet));
        int bytes;

        if (sign!=-1 && cli_socks[i]) {
          printf("about to read from cli sock\n");
          bytes = read(cli_socks[i], data, sizeof(struct packet));
          printf("made it out\n");
        }

        if (sign==-1) {
          data->type = PACKET_KILL;
          write(cli_socks[i], data, sizeof(struct packet));
          close(cli_socks[i]);
          i--;
          SIZEOF--;
          if (SIZEOF<=i) {
            exit(0);
          }
        } else if (!bytes) {
          close(cli_socks[i]);
          removeIndex(cli_socks, 10, i);

          i--;
          SIZEOF--;
        } else if (sign==1) {
          data->type = PACKET_STOP;
          bytes = write(cli_socks[i], data, sizeof(struct packet));
          err(bytes, "Server error");
        } else {
          if (cli_socks[i]) {
            subserver_logic(cli_socks[i]);
          }
        }
      }
    }
  }
}
