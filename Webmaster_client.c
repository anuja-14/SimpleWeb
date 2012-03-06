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
    
    // TODO : Add the version number here and then finally add the LRCR end to the line and send the request back to the calling function.



}
