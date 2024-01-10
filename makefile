.PHONY: compile clean Server Client

compile: client server

Server: server
	@./server $(ARGS)
Client: client
	@./client $(ARGS)

client: client.o util.o
	@gcc -o client client.o util.o

server: server.o util.o
	@gcc -o server server.o util.o

client.o: client.c util.h
	@gcc -c client.c

server.o: server.c util.h
	@gcc -c server.c

util.o: util.c
	@gcc -c util.c

clean:
	@rm *.o client server -f