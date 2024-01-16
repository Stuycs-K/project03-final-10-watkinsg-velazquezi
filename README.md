[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# Bogo Sort

### Bogus

Gus Watkins

Israel Velazquez Rugama
       
### Project Description:

The project is to create a Distributed computing tool to have bogo sort run on several terminals. We'll show the progress update of each client and potentially display their progress
  
### Instructions:

The user must have the makefile, server.c, util.c, util.h, and client.c in the same directory
a user may compile the program using 'make compile'
a user may run the program as the server using 'make Server'
a user may run the program as the client using 'make Client $(ARGS)'

as the server, the user interacts with the program by using the following commands:
start - initializes the original array and sends them to the clients
display - displays the clients bogoSorting
stop - clients end their bogoSort loop, and wait for new input
kill - Clients are disconnected from the server
