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

// TODO : Not sure of how to use the environment variable . Have to check up on that to get the version number. 
char * create_request_line ( char* method , char* file_path )
{
    char * request[100];
    char protocol_name[10] = "Webmaster";
    int i;
    strcpy( request , method );

    int j = strlen(method);
    for ( i = 0 ; i < strlen(file_path) ; i++ )
    {
        // j+1+i because we want to have one blank space in between the method and the path .     
        // Ex : GET www.google.com ( j = 3 , request[4] = "w"  , 4 = j + 1 + 0 (i)
        reply[j+1+i] =  file_path[i];
    }
    
    j = j+1+i;  // Again increase j by 1 so as to have the space between file_name and protocol

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

char * create_packet ( char * method , char * file_path , char * optional_message )
{
    char request[100];
    int i,j,k;

    char * packet_line = create_request_line ( method , file_path );
    for ( i = 0 ; i < strlen(first_line) ; i++ )
    {
        request[i] = first_line[i];
    }
    request[i] = "\n";
    request[i+1] = "\n";
    i=i+2;

    packet_line = create_header_line ();
    for ( j=0;  j< strlen(packet_line) ; j++ )
    {
        request[i+j] = packet_line[j];
    }
    request[i+j] = "\n";
    j =j+1;
    packet_line = message_body ( optional_message );

    for ( k = 0 ; k < strlen(packet_line) ; k++ )
    {
        request[i+j+k] = packet_line[k];
    }
    request[i+j+k] = '\0';

    return request;
}

char * test_simple_browser ( char * file_to_path )
{
    
}

