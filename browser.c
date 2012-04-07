/*
 * =====================================================================================
 *
 *       Filename:  browser.c
 *
 *    Description:  The C code behind the opening of the page i.e the browser function 
 *
 *        Version:  1.0
 *        Created:  Monday 5 March 2012 05:07:08  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Authors:  
 *                  Vaibhav Agarwal , vaisci310@gmail.com
 *                  Anuja Agarwal , 
 *
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXDATASIZE 100
#define MAX_URL_LENGTH 100

// Get the address from the struct hiding whether the addressing is IPv4 or IPv6.
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[],char* envp[])
{
    char *method;
    int sockfd, numbytes;
    char buf[MAXDATASIZE], reply[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN] ;

    char *file;

    if (argc != 3) 
    {
        fprintf(stderr,"usage: ./client server_name port\n");
        exit(-1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;        // To set up a TCP protocol ( connection oriented )

    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(-1);
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) 
        {
            perror("client: socket");
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }
        break;
    }
    if (p == NULL) 
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    // Net to presentation of the ip address for easier human reading .
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),s, sizeof s);

#ifdef DEBUG
    printf("client: connecting to %s\n", s);
#endif

    freeaddrinfo(servinfo); // all done with this structure

    // Get the file name from the python browser. Once that is done , send the corresponding link to the server .
    // For now , lets take it from the user.
//    printf("Enter the URL of the file that you would like to view : \n");
  //  scanf("%s" , file );
  //  The following environmental variables are set by the python script which calss this client code
    file = getenv("FILE_PATH");
    method = getenv("METHOD");
    printf("file %s", file);

    printf("METHOD %s", method);
    char packet[MAXDATASIZE];
     create_packet(method, file, "", packet);


    if ( send ( sockfd , packet , MAXDATASIZE -1 , 0 ) == -1 )
    {
        perror("Send ");
        exit(-1);
    }

    // Once sent , wait for the server to reply . As and when the server replies , you have to extract the data and write it to a file . The python script will read the file and display the file to the user using the browser.
    return 0;
}


