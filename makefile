CC = gcc
strict_options = -Wall -pedantic

all: client server

server: server.o Webmaster_server.o
	gcc -g -o server server.o Webmaster_server.o

client: client.o Webmaster_client.o
	$(CC) -g -o $@ client.o Webmaster_client.o

server.o : server.c
	gcc -g -c server.c

client.o: client.c
	gcc -g -c $<

Webmaster_server.o: Webmaster_server.c
	gcc -g -c $<

Webmaster_client.o: Webmaster_client.c
	gcc -g -c $<
clean:
	rm -f *.o
	rm -f server client

