# Dev Log:

## Gus Watkins

### 2024-01-03 - Brief description
Brainstormed for project ideas, then thought through the general implementation and began work on PROPOSAL.md

### 2024-01-04 - proposal+begin initial server
Wrapped up work on the proposal and began working on a basic server

### 2024-01-05 - Client-server communication work, select()
Worked on figuring out how the client and server should communicate, and ended up with a `struct packet` in `networking.h`.
Spent the rest of the time figuring out `select()` and how to use it in the server to manage all the clients without forking.

### 2024-01-08 - Nearly-functional select() based server
Spent the day working in server.c, making the server be able to manage information coming from multiple sources.
Most of the networking is done, except for array add/remove for multiple clients. Needs testing.

### 2024-01-09 - Debugging server
It isn't able to read from stdin if you don't write to it before the first client connects - spent most of the period trying to figure that out.
Israel started working on a band-aid fix (which I plan to finish).

### 2024-01-10 - THE SERVER WORKS!!!
Spent the day debugging the server with Israel. Turns out that select() removes file descriptors in the fd_set that don't have data to read, even though this isn't necessary and that it doesn't mess with `FD_ISSET`. :/

### 2024-01-11 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-12 - Brief description
Expanded description including how much time was spent on task.

## Israel Velazquez

### 2024-01-03 - worked on readme / proposal
Came up with ideas to potentially work on for the group project. Finished the basic readme tasks that required very little work in order to get us started. Current working idea is bogo sort on many different computers
Added base codefiles and makefile, potentially to be changed later

### 2024-01-04 - finished the proposal
worked on the proposal and talked about the pacing of how we will do our assignment
Updated the network file with methods in order to make sure it compiles and added some code to the client to make it connect to the server

### 2024-01-05 - Client recieving / sorting
Worked on the variables the client uses to recieve the data from the server, and starting to work on how to make the seeds work with bogosort
Finished BogoSort, added send feature to client, added to the server, included color

### 2024-01-08 - Completed Bogo, working on server visuals
The BogoSort now works randomly based off of the seed you give it, and the server now has the method made to show visuals once it's ready to show off it's clients. Has different colors to help see the difference
Added a better random method, print statement to cknfirm if client could was working, and removed unnecessary code. Reading server now as it's what I have to transition to

### 2024-01-09 - Polished client, bandaded Server
In class I finished up the client, making it handle the Server's output slightly differently and more efficiently. Added a bandaid solution for a bug
At home I added signal handling, including SIGINT and SIGQUIT which will be very useful as inputs for our presentation

### 2024-01-10 - Fixed Server, added new util methods
Helped fix the select issue where the file descriptors were being cleared after every slect call. Added a new method to find the biggest value in an array given the size of the array
The server now quits successfully on ^C, while closing the clients. discovered the remove method needed to tell clients to close

### 2024-01-11 - Aligned the Client and Server
The Client and Server now write and read the same number of times. Server now handles stopping clients midway through their bogosorting. Seemed to have ecountered an issue with client only going through the loop once
At home yesterday (I passed out cause I was up so late. Sorry for not updating), I worked some more on finalizing the signals, and discovered that ctrl+z can help close the terminal while we get ^C working 

### 2024-01-12 - Debugging as well as working on the print statment
Expanded description including how much time was spent on task.
Working on putting the printing in the Clients