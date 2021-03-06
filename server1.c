#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#define MAX_URL_LENGTH 1024
#define MAX_DATA_SIZE 1024
char LR = 0x0A;
char CR = 0x0D;

// Using Ctrl-C to stop the process
/*
void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}
*/
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


char* get_file_path(char* recv_data)
{
     int cnt = 0;    
    char file_path[MAX_URL_LENGTH];
    while(recv_data[cnt] != LR)
    {
         file_path[cnt] = recv_data[cnt];
    }
    file_path[cnt] = '\0';
    printf("file_path %s", file_path);
}


int main(int argc, char** argv)
{

    int serverSockID, connection, true = 1, sendBytes;
    struct sockaddr_in serverAddr, clientAddr;
    int sin_size, bytes_recieved;
    char recvData[1024], sendData[1024], filePath[1024];
    int pid;
    FILE* fp;
    char * file_path;
    


    if ((serverSockID = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }

    if((setsockopt(serverSockID, SOL_SOCKET,SO_REUSEADDR, &true, sizeof(int))) == -1)
    {
        perror("SetSockOpt");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(serverAddr.sin_zero), 8);

    if((bind(serverSockID, (struct sockaddr*) &serverAddr, sizeof(struct sockaddr))) == -1)
    {
        perror("Unable to bind");
        exit(1);
    }

    if(listen(serverSockID, 5) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("\n Server on \n");
    fflush(stdout);

    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);

        connection =  accept(serverSockID, (struct sockaddr *)&clientAddr, &sin_size);
        printf("\n Client %s Connected to port %d", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        pid = fork();

        if(pid == 0) //child process 
        {
            bytes_recieved = recv(connection, recvData, 1024, 0);

            recvData[bytes_recieved] = '\0';
            if(strcmp(recvData, "q") == 0 || strcmp(recvData, "Q") ==0)
            {
                close(connection);
                break;
            }
            else
            {
                printf("\nRecieved Data = %s ", recvData);
                file_path = get_file_path(recvData);
		
                if((fp = fopen(file_path, "r")) == NULL)
                {
                    printf("\nFile I/O  Fail");
                    printf("\nFile Data Sent Quit : " );
                    gets(sendData);
                    if((sendBytes = send(connection, sendData, strlen(sendData), 0)) == -1)
                    {
                        perror("SEND");
                    }
                    close(connection);
                    continue;
                }
                fflush(stdout);
            }

            fseek(fp, 0, SEEK_SET);

            while(fgets(sendData, sizeof(sendData), fp) != NULL)
            {
                if((sendBytes = send(connection, sendData, strlen(sendData), 0)) == -1)
                {
                    perror("SENDBYTES");
                    exit(1);
                }

            }

            printf("\nFile Data Sent Quit : " );
            gets(sendData);
            if((sendBytes = send(connection, sendData, strlen(sendData), 0)) == -1)
            {
                perror("SEND");
                exit(1);
            }
            close(connection);
        }
        else
        {
            close(connection);
        }
    }
    close(serverSockID);
    fclose(fp);
    return 0;
}


