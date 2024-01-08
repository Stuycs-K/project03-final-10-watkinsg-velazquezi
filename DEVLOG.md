# Dev Log:

## Gus Watkins

### 2024-01-03 - Brief description
Brainstormed for project ideas, then thought through the general implementation and began work on PROPOSAL.md

### 2024-01-04 - proposal+begin initial server
Wrapped up work on the proposal and began working on a basic server

### 2024-01-05 - Client-server communication work, select()
Worked on figuring out how the client and server should communicate, and ended up with a `struct packet` in `networking.h`.
Spent the rest of the time figuring out `select()` and how to use it in the server to manage all the clients without forking.

### 2024-01-08 - Brief description
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