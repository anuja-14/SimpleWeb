#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main( int argc, char *argv[] )
{

  FILE *fp;
  int status;
  char path[1035];
  char Filename[100];

  char temp[1000];
  temp[0] = '\0';
  strcat(temp, "python history.py anuja");
  temp[22] = '\0';
//  strcat(temp, "README");

  /* Open the command for reading. */
  fp = popen(temp, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit;
  }


  /* Read the output a line at a time - output it. */
  /* close */
  pclose(fp);

  return 0;
}

