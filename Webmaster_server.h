/*
 * =====================================================================================
 *
 *       Filename:  Webmaster_client.h
 *
 *    Description:  Header file containing functions regarding Webmaster protocol for the client
 *
 *        Version:  1.0
 *        Created:  Tuesday 06 March 2012 06:42:37  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vaibhav Agarwal (), vaisci310@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef WEBMASTER_H
#define WEBMASTER_H

// Protocol version can be a environment variable like the header line variables.
void create_request_line ( char * method , char * file_path, char*  );
// We can set the header's based on environment variables that can be set when the browser is opened.
char * create_header_line (); 
char * message_body(char * optional_message);

void create_packet( char * HTTP_VERSION , char * status_code , char * file_data, char* packet );



#endif
