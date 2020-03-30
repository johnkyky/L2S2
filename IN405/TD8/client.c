#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>



int check_max_argument(const int main_argc)
{
	int number_value = 0;

	int fd = open("/tmp/million/.config", O_RDONLY);

	if(fd == -1)
	{
		fprintf(stderr, "[ERROR] There is no ongoing lottery\n");
		exit(2);
	}

	read(fd, &number_value, sizeof(int));
	close(fd);

	if((main_argc - 2) > (number_value))
	{
		fprintf(stderr, "[ERROR] too much arguments\n");
		exit(-1);
	}

	return 0;
}


int send_message(const int main_argc, char** main_agv)
{
	printf("my pid : %d\n", getpid());
	char message_sent[64];
	snprintf(message_sent, 64, "%d %d ", getpid(), main_argc - 2);
	for(int i = 2; i < main_argc; i++)
	{
		strcat(message_sent, main_agv[i]);
		strcat(message_sent, " ");
	}


	FILE* f = fopen("/tmp/million/client.ff", "w");
	if(!f)
	{
		printf("f = NULL\n");
		exit(0);
	}

	fprintf(f, "%s", message_sent);

	fclose(f);

	return 0;
}


int received_message(const char* path)
{
	char message_received[64];

	int fd = open(path, O_RDONLY);
	read(fd, &message_received, 64);
	close(fd);

	int count, gain;
	sscanf(message_received, "%d %d", &count, &gain);
	printf("message_received : Tu as trouve %d numero, tu repars avec %d$!\n", count, gain);

	if(!count)///voir a la fin pour les code de retour du programme client
		return 1;

	return 0;
}



int main(int argc, char** argv)
{
	check_max_argument(argc);

	char path_fifo[64];
	snprintf(path_fifo, 64, "/tmp/million/%d.ff", getpid());

	mkfifo(path_fifo, 0666);

	send_message(argc, argv);

	received_message(path_fifo);

	unlink(path_fifo);

	exit(0);
}


/*/////////////////////////////////////////////////////////////////////////////////////
	4 code de retour differents pour client
		- 0 le client c est correctement execute mais n a pas trouve de nombre
		- 1 le client c est correctement execute et a trouve au moins un nombre gagnant
		- 2 le client c est correctement execute mais n a pas pu joue
		- -1 le client ne c est pas execute correctement
/////////////////////////////////////////////////////////////////////////////////////*/