#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdarg.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

char *analyzePacket ( char * packet , char * message)
{
    int cnt = 0,cnt_message = 0;    
    char changed;
    while(packet[cnt] != ' ')
    {
        cnt++;
    }
    while(recv_data[cnt] != ' ')
    {
        changed = recv_data[cnt];
        cnt++;
        cnt++;
        if ( changed == '1' )
        {
            message[cnt_message]=packet[cnt];
            cnt++;
            cnt_message++;
        }
        else
            return NULL;
    }
}

int main(int argc, char** argv)
{
	FILE *fp;
	int clientSockID, bytes_recieved, sentBytes;
	char packet[1024];
	char *file_path, recvData[1024];
	struct hostent *host;
	struct sockaddr_in serverAddr;
	struct timeval timeout;
	host = gethostbyname((char *)argv[2]);

    // Not able to connect to the server . Error and exit
	if((clientSockID = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket");
		exit(1);
	}
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr = *((struct in_addr *)host -> h_addr);
	bzero(&(serverAddr.sin_zero), 8);

	if(connect(clientSockID, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("connect");
		exit(1);
	}

//	gets(file_path);
	file_path = argv[3];

	create_packet("GET",file_path, "", packet);
	if( (sentBytes =  send(clientSockID, packet, strlen(packet), 0)) == -1)
	{
		perror("sentBytes");
	}
	int cnt = 0;
    char *BASE_URL = "cache/";
    char * fileSave = strcat(BASE_URL , file_path );
	fp = fopen(fileSave, "w");
	while(1)
	{
		bytes_recieved = recv(clientSockID, recvData, 1024 , 0);
		recvData[bytes_recieved] = '\0';
		if (recvData[0] == 0x0D)
		{
			printf("File Recieved \n");
			close(clientSockID);
			break;
		}
		else
		{	
            char * message;
            analyzePacket( bytes_recieved , message );
            if ( message != NULL )
            {
                fprintf(fp, recvData);
                recvData[bytes_recieved] = '\0';
                printf("\nRecieved data = %s " , recvData);
            }
		}
		cnt++;
	}
	fclose(fp);

}

