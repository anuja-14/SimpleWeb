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
    fflush(stdout);
   while(packet[cnt] != ' ')
    {
        cnt++;
    }
    cnt++;
    changed = packet[cnt];
    cnt++;
    cnt++;
  
    while(packet[cnt] !=0x0D)
    {
        if ( changed == '2' )
        {
            message[cnt_message]=packet[cnt];
            cnt++;
            cnt_message++;
        }
        else
           return NULL;
    }
    
            //printf("%s \n" , message);
    fflush(stdout);
 
}

int main(int argc, char** argv)
{
	FILE *fp;
	int clientSockID, bytes_recieved, sentBytes;
	char packet[2048];
	char *file_path, recvData[2048];
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
    //printf("File to be got : %s " , file_path );
    fflush(stdout);

	create_packet("GET", file_path, "", packet);
    //printf("Packet is %s \n",packet);
    fflush(stdout);
	if( (sentBytes =  send(clientSockID, packet, strlen(packet), 0)) == -1)
	{
		perror("sentBytes");
	}
	int cnt = 0;
    char *BASE_URL = "cache/";
    char fileSave[100];
    fileSave[0] = '\0';
    strcat(fileSave , BASE_URL );
    strcat(fileSave , file_path);
    //printf("The file is %s " , fileSave );
    fflush(stdout);
	fp = fopen(file_path, "w");
    int count = 0;
	while(1)
	{
        if (count > 40)
            break;
        count++;
		bytes_recieved = recv(clientSockID, recvData, 2048 , 0);
		if (recvData[0] == 0x0D)
		{
			close(clientSockID);
			break;
		}
		else
		{	
		recvData[bytes_recieved] = '\0';
            char message[2048];
            analyzePacket( recvData , message );
            if ( message != NULL )
            {
                fprintf(fp, recvData);
                recvData[bytes_recieved] = '\0';
                //printf("\nRecieved data = %s " , recvData);
            }
		}
		cnt++;
	}
	fclose(fp);

}

