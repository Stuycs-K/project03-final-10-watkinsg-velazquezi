#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <sys/select.h>

#define PACKET_KILL -2
#define PACKET_STOP -1
#define PACKET_REQUEST 0
#define PACKET_RESULT 1
#define PACKET_INFO 2

#define TOTAL_SEEDS 30
#define PACKET_SIZE 10
#define PACKET_SEEDS 10
#define MAX_CLIENTS 10


struct packet {
    int type;
    int arr[PACKET_SIZE];
    int seeds[PACKET_SEEDS];
};


#ifndef NETWORKING_H
#define NETWORKING_H
#define PORT "19230"
#define BUFFER_SIZE 1024
void copyArr(int dest[], int copying[], int size);
int ranPos(int size);
int amountOfClients(int cli_socks[]);
void err(int i, char*message);
int server_setup();
int client_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);
int clientLogic(int server_socket);
int subserver_logic(int client_socket, int arr[]);
void removeIndex(int arr[], int size, int index);
void appendArr(int arr[], int newData);
int findHighest(int arr[], int size);
void printData(int arr[]);
#endif
