#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>


#define SERVER "server"
#define CLIENT "client"



bool verif_client(const int argc, char** argv)
{
	for(int i = 2; i < argc; i++)
		for(int j = 0; j < strlen(argv[i]); j++)
			if(!isdigit(argv[i][j]))
				return false;
	return true;
}



int main(int argc, char** argv)
{
	if(argc == 1)
		fprintf(stderr, "[ERROR] Please puts argument\n");
	else if(!strcmp(argv[1], SERVER) && argc == 3)
	{
		char* argument[] = {"server", argv[2], NULL};
		execv("./.server", argument);
	}
	else if(!strcmp(argv[1], CLIENT) && verif_client(argc, argv))
		execv("./.client", argv);
	else
		fprintf(stderr, "[ERROR] Arguments invalid\n");

	return 0;
}