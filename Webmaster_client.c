/*
 * =====================================================================================
 *
 *       Filename:  Webmaster_client.c
 *
 *    Description:  Functions for the Webmaster protocol for the client
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
#include "Webmaster_client.h"

char CR = 0x0D;
char LR = 0x0A;


// TODO : Not sure of how to use the environment variable . Have to check up on that to get the version number. 
void create_request_line ( char* method , char* file_path, char* reply )
{
   //  char request[100];
    char protocol_name[10] = "Webmaster";
    int i;
    strcpy( reply , method );

    int j = strlen(method);
    reply[j] = ' ';
    for ( i = 0 ; i < strlen(file_path) ; i++ )
    {
        // j+1+i because we want to have one blank space in between the method and the path .     
        // Ex : GET www.google.com ( j = 3 , request[4] = "w"  , 4 = j + 1 + 0 (i)
        reply[j+1+i] =  file_path[i];
    }
    reply[j+i+1]=' '; 
    j = j+2+i;  // Again increase j by 1 so as to have the space between file_name and protocol

    for ( i = 0 ; i < strlen(protocol_name) ; i++ )
    {
        reply[j+i] = protocol_name[i];
    }

    reply[j+i] = '/';
    
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

void create_packet ( char * method , char * file_path , char * optional_message, char* request )
{
    int i,j,k;
    char *packet_line;
    char first_line[100];
    create_request_line ( method , file_path, first_line );
    for ( i = 0 ; i < strlen(first_line) ; i++ )
    {
        request[i] = first_line[i];
    }
    request[i] = LR;
    i++;
    if ( optional_message != NULL )
    {
        for ( j = 0 ; j < strlen(optional_message) ; j++ )
        {
            request[i] = optional_message[j];
            i++;
        }
    }
    request[i] = '\0';
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
}

/*
char * test_simple_browser ( char* method_name, char * file_to_path )
{
    char optional_message[10] = "";
    char packet[100] = create_packet(method_name, file_to_path, method);
}
*/
