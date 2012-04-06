#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[], char*envp[])
        {
           // printf("%s", getenv("FILE_PATH"));
		FILE * fp;
fp = fopen("client.c", "r");
printf("%d", fp);

        }
