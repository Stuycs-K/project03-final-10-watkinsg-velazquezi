# Final Project Proposal

## Group Members:

Gus Watkins

Israel Velazquez Rugama
       
# Intentions:
    
The goal of this project is to create a tool for easy distributed computing. The server will send tasks to connected machines and handle results coming from clients.

# Intended usage:

One machine will be used as a server and will run a program that opens a port. Any number of client machines can connect to that port to join the distributed project.
  
# Technical Details:

There will be two main programs - the client and the server. We will use what we learned about networking to handle the initial connection, what we learned about files to manage multiple clients on the server and send data back and forth, and what we learned about processes to let clients run the task in multiple threads.


It depends on how long things will take, but in general:
- Israel will create the bogosort and work on the client
- Gus will work on the server


We'll be using arrays to manage the socket descriptors for the client and for the bogosort input and output. We may use structs to represent information about each bogosort 'attempt', including the resulting array and the random seed used to produce it.
    
# Intended pacing:

A timeline with expected completion dates of parts of the project.

TODO