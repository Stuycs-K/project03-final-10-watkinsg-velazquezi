#include "util.h"

void copyArr(int dest[], int copying[], int size) {
  for (int i=0; i<size; i++) {
    dest[i] = copying[i];
  }
}

void removeIndex(int arr[], int size, int index) {
  for (int i = index; i < size - 1; i++) {
    arr[i] = arr[i+1];
  }
  arr[size - 1] = 0;
}

void appendArr(int arr[], int newData) {
  for (int i=0; i<MAX_CLIENTS; i++) {
    if (!arr[i]) {
      arr[i]=newData;
      i += MAX_CLIENTS;
    }
  }
}

int findHighest(int arr[], int size) {
  int biggest = -1;
  for (int i=0; i<size; i++) {
    if (arr[i]>biggest) {
      biggest = arr[i];
    }
  }
  return biggest;
}

void bogoSort(int arr[], int size, int random, int copy[]) {
  srand(random);
  copyArr(copy, arr, size);
  for (int i=0; i<size; i++) {
    int x = rand()%size;
    int temp = copy[x];
    copy[x] = copy[i];
    copy[i] = temp;
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

int ranPos(int size) {
  int r_file = open("/dev/random", O_RDONLY , 0);
  int buff[size];
  size = read(r_file, buff, size);
  err(size, "RandomPositive's error");
  int number = 0;
  int increase = 0;
  int index = 1;
  for (int i=1; i<=size; i++) {
    number+=buff[i-1]<<increase;
    if (increase==0) {
      increase++;
    }
    increase<=2;
    index*=2;
  }
  number %= index;
  if (number<0) {
    number*=-1;
  }
  return number;
}

int client_tcp_handshake(char * server_address) {

  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  getaddrinfo(server_address, PORT, hints, &results);
    //Server sets node to NULL

  //getaddrinfo
  
  int sd = socket(results->ai_family, results->ai_socktype, 0);
  err(sd, "Failed");
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

  int arr[PACKET_SIZE];
  int copy[PACKET_SIZE];
  int seeds[PACKET_SEEDS];
  /* 
    What does client do? 
    {
      connect - block (int handshake)
      while (1) {
        read - once
        for (int i=0; i<PACKET_SEEDS; i++) {
          read then write PACKET_SEED times until it stops
        }
      }
    }
  */

  while (1) {
    read(server_socket, data, sizeof(struct packet));
    int type = data->type;
    copyArr(arr, data->arr, PACKET_SIZE);
    copyArr(seeds, data->seeds, PACKET_SIZE);

    if (type==PACKET_REQUEST) {
      for (int i=0; i<PACKET_SEEDS; i++) {

        // allow for stop/kill while doing bogosorts (Stretch goal)
        if (!seeds[i]) {
          bogoSort(arr, PACKET_SIZE, seeds[i], copy);

          data->type = PACKET_RESULT;
          copyArr(data->arr, copy, PACKET_SIZE);

          read(server_socket, data, sizeof(struct packet));
          if (!data->type) {
            write(server_socket, data, sizeof(struct packet));
            printf("Client has sent back a possible solution");
            sleep(3);
          }
          else if (data->type==-1) {
            i+=PACKET_SEEDS;
          }
        }
      }
    }
    else if (type==PACKET_KILL) {
      close(server_socket);
      exit(0);
    }
  }
}

void printData(int arr[]) {
  for (int i=0; i<PACKET_SIZE; i++) {
    if (arr[i]) {
      int color = (i%8)+30;
      for (int j=0; j<arr[i]; j++) {
        printf("\e[0;%d>", color);
      }
      printf("\e[40m\n");
    }
  }
}

int subserver_logic(int client_socket) {
  struct packet *data = malloc(sizeof(struct packet));
  int arr[PACKET_SIZE];
  data->type = PACKET_REQUEST;
  write(client_socket, data, sizeof(struct packet));
  read(client_socket, data, sizeof(struct packet));
  copyArr(arr, data->arr, PACKET_SIZE);
  
  printData(arr);
}

int server_tcp_handshake(int listen_socket){
  int client_socket;

  //accept the client connection
  client_socket = accept(listen_socket, NULL, NULL);
  
  return client_socket;
}