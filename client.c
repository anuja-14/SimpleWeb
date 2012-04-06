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

int main(int argc, char** argv)
{
	FILE *fp;
	fp = fopen("test.html", "w");
	int clientSockID, bytes_recieved, sentBytes;
	char packet[1024];
	char file_path[1024], recvData[1024];
	struct hostent *host;
	struct sockaddr_in serverAddr;
	struct timeval timeout;
	host = gethostbyname((char *)argv[2]);

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

	printf("\nConnection Established : Enter File URL : ");
	gets(file_path);

	create_packet("GET",file_path, "", packet);
	if( (sentBytes =  send(clientSockID, packet, strlen(packet), 0)) == -1)
	{
		perror("sentBytes");
	}
	int 	cnt = 0;
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
			fprintf(fp, recvData);
			recvData[bytes_recieved] = '\0';
			printf("\nRecieved data = %s " , recvData);
		}
		cnt++;
	}
	fclose(fp);

}
