/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  Server for web browser interface
 *
 *        Version:  1.0
 *        Created:  Saturday 10 March 2012 02:06:37  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *                  Anuja Agrawal, anujaagrw@gmail.com
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
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define BACKLOG 10
#define MAX_URL_LENGTH 100
#define MAX_DATA_SIZE 1024

#define MESSAGESIZE 100

char LR = 0x0A;
char CR = 0x0D;

// Using Ctrl-C to stop the process
void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


void get_file_path(char* recv_data, char *file_path)
{
    int cnt = 0,cnt_file = 0;    
    char method[MAX_DATA_SIZE];
    while(recv_data[cnt] != ' ')
    {
        method[cnt] = recv_data[cnt];
        cnt++;
    }
    cnt++;
    while(recv_data[cnt] != ' ')
    {
        file_path[cnt_file] = recv_data[cnt];
        cnt++;
        cnt_file++;
    }
    file_path[cnt_file] = '\0';
    printf("file_path %s", file_path);
}

char* get_method(char* recv_data)
{
}

char* getHeaders()
{
}

char* getMessageBody()
{
}

void process(char *recv_data, int connection)
{
    char file_path[MAX_URL_LENGTH];
    get_file_path(recv_data, file_path);
    FILE *fp;
    char file_data[MAX_DATA_SIZE];
    int sentBytes;
    printf("file path in process %shello", file_path);
    if((fp = fopen(file_path, "r")) == NULL)
    {
        printf("\nFile I/O  Fail");
        printf("\nFile Data Sent Quit : " );
        gets(file_data);
        if((sentBytes = send(connection, file_data, strlen(file_data), 0)) == -1)
        {
            perror("SEND");
        }
        close(connection);
    }

    fseek(fp, 0, SEEK_SET);

    while(fgets(file_data, sizeof(file_data), fp) != NULL)
    {
        printf("%s sending data", file_data);
        if((sentBytes = send(connection, file_data, 1024, 0)) == -1)
        {
            perror("SENDBYTES");
            exit(1);
        }
    }
    file_data[0] = CR;
    if((sentBytes = send(connection, file_data, strlen(file_data), 0)) == -1)
    {
        perror("SENDBYTES");
        exit(1);
    }


    // FILE DATA SENT
}

int main( int argc , char * argv[] )
{
    int sockfd , new_fd , return_value , numbytes ;
    struct addrinfo hints , * servinfo , *p;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    char request[MESSAGESIZE];
    char file_data[MAX_DATA_SIZE];
    struct sigaction sa;
    int sentBytes;

    memset(&hints , 0 , sizeof hints );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;        // Server needs to listen at localhost . So the AI_PASSIVE flag

    if ( argc != 2 )
    {
        printf("Usage : ./server <port_no> \n");
        exit(-1);
    }

    if ( (return_value = getaddrinfo ( NULL , argv[1] , &hints , &servinfo ) ) != 0 )
    {
        fprintf(stderr , "getaddrinfo : %s\n" , gai_strerror(return_value) );
        exit(-1);
    }

    for ( p = servinfo ; p!=NULL ; p = p->ai_next )
    {
        // Create socket for each of the possible connections
        if ( ( sockfd =  socket ( p->ai_family , p->ai_socktype , p->ai_protocol) ) == -1 )
        {
            perror("server:socket");
            continue;
        }
        // Bind the socket to the appropriate port . 
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }
        break;
    }
    if (p == NULL) 
    {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure . Not needed any more

    if (listen(sockfd, BACKLOG) == -1)          // Too many connections waiting . In such a case exit 
    {
        perror("listen");
        exit(-1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(1);
    }
    printf("server: waiting for connections...\n");
    sin_size = sizeof their_addr;
    while(1)  // main accept() loop
    {
        // The accept command here creates a new file descriptor in case a connection is established.
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

        if (new_fd == -1) 
        {
            perror("accept");
            exit(-1);
        }

        // ntop stands for network to presentation
        inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr *)&their_addr),s, sizeof s);
        //        printf("server: got connection from %s\n", s);

        // Fork is necessary so that server can listen for other clients and respond to their requests as well.
        if (!fork()) 
        {
            // this is the child process
            close(sockfd); // child doesn't need the listener
            char recv_data[MAX_DATA_SIZE];
            int bytes_received = recv(new_fd, recv_data, MAX_DATA_SIZE, 0);
            printf("%s recv_data", recv_data);
            process(recv_data, new_fd);

            // Now generate the header line , and other lines based on the protocol and send the resultant packets to the client for it to display the same to the user.For now , we are only going to look at text data . Then later on , we can think of images too.
            // Once that is done , stop the present child and wait for further connections.
            exit(1);
        }
        // New_fd of the parent is distinct from the child and so should be closed separately.
        close(new_fd);
    }
    return 0;
}

