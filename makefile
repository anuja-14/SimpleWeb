CC = gcc
strict_options = -Wall -pedantic

all: client server

server: server.c
	gcc -g -o server server.c

client: browser.o Webmaster_client.o
	$(CC) -g -o $@ browser.o Webmaster_client.o

browser.o: browser.c
	gcc -g -c $<

Webmaster_client.o: Webmaster_client.c
	gcc -g -c $<

