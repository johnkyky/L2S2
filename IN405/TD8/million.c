#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define SERVER "server"
#define CLIENT "client"


int main(int argc, char** argv)
{
	if(!strcmp(argv[1], SERVER))
	{
		char* argument[] = {"server", argv[2], NULL};
		execv("./server", argument);
	}
	else if(!strcmp(argv[1], CLIENT))
	{
		execv("./client", argv);
	}

	return 0;
}