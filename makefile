CC = gcc
strict_options = -Wall -pedantic

all: client server

server: server.c
	gcc -g -o server server.c

client: client.o Webmaster_client.o
	$(CC) -g -o $@ client.o Webmaster_client.o

client.o: client.c
	gcc -g -c $<

Webmaster_client.o: Webmaster_client.c
	gcc -g -c $<
clean:
	rm -f *.o
	rm -f server client
