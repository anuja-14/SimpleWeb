/*
 * =====================================================================================
 *
 *       Filename:  Webmaster_server.c
 *
 *    Description:  Functions for the Webmaster protocol for the server
 *
 *        Version:  1.0
 *        Created:  Tuesday 06 March 2012 07:06:24  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal , vaisci310@gmail.com
 *         Points Learnt : 
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Webmaster_server.h"
#define MAX_DATA_SIZE 2048
char CR = 0x0D;
char LR = 0x0A;


// TODO : Not sure of how to use the environment variable . Have to check up on that to get the version number. 
void create_initial_line ( char* HTTP_VERSION , char* status_code, char* initial_line )
{
   //  char request[100];
    int i;
    strcpy( initial_line , HTTP_VERSION );

    int j = strlen(HTTP_VERSION);
    initial_line[j] = ' ';
    for ( i = 0 ; i < strlen(status_code) ; i++ )
    {
        // j+1+i because we want to have one blank space in between the method and the path .     
        // Ex : GET www.google.com ( j = 3 , request[4] = "w"  , 4 = j + 1 + 0 (i)
         initial_line[j+1+i] =  status_code[i];
    }
    initial_line[j+i+1]=LR; 
    /*  j = j+2+i;  // Again increase j by 1 so as to have the space between file_name and protocol

    for ( i = 0 ; i < strlen(string_output) ; i++ )
    {
        initial_line[j+i] = string_output[i];
    }

	initial_line[j+i]='\0';*/
    
    // TODO : Add the version number(ENV variable) here and then finally add the LRCR end to the line and send the request back to the calling function.
}

char * create_header_line ()
{
    // TODO : Again , based on the ENV variables we have to create the appropriate header_line and send the packet.

}

char * message_body ( char * optional_message )
{
    // TODO : Add a LRCR at the end of the message and send it back to the caller to create the whole packet to be sent.
}

void create_packet ( char * HTTP_VERSION , char * status_code , char * file_data, char* request )
{
    int i,j,k;
    char initial_line[MAX_DATA_SIZE];
    create_initial_line ( HTTP_VERSION , status_code, initial_line );
    for ( i = 0 ; i < strlen(initial_line) ; i++ )
    {
        request[i] = initial_line[i];
    }
    for(j = 0; j< strlen(file_data);j++)
	{
	request[i+j] = file_data[j]; 
	}
	request[i+j] = CR;
	request[i+j+1] = '\0';
}
   /* 
    i=i+1;

    packet_line = create_header_line ();
    for ( j=0;  j< strlen(packet_line) ; j++ )
    {
        request[i+j] = packet_line[j];
    }
    request[i+j] = CR;
    j =j+1;
    packet_line = message_body ( optional_message );

    for ( k = 0 ; k < strlen(packet_line) ; k++ )
    {
        request[i+j+k] = packet_line[k];
    }
    request[i+j+k] = CR;
    request[i+j+k+1]= LR;
*/

/*
char * test_simple_browser ( char* HTTP_VERSION_name, char * file_to_path )
{
    char optional_message[10] = "";
    char packet[100] = create_packet(HTTP_VERSION_name, file_to_path, method);
}
*/
