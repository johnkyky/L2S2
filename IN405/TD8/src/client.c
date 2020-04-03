#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>


#define PATH_CONFIG "/tmp/.config"
#define PATH_CLIENT "/tmp/client.ff"
#define STRING_SIZE 64


int check_max_argument(const int main_argc)
{
	int number_value = 0;

	int fd = open(PATH_CONFIG, O_RDONLY);

	if(fd == -1)
		return 2;

	int error = read(fd, &number_value, sizeof(int));
	if(error == -1)
	{
		perror("ERROR]");
		return error;
	}

	error = close(fd);
	if(error)
	{
		perror("ERROR]");
		return -1;
	}

	if((main_argc - 2) > (number_value))
		return -1;
	else if(main_argc == 2)
		return -1;

	return 0;
}


int send_message(const int main_argc, char** main_agv)
{
	char message_sent[STRING_SIZE];
	snprintf(message_sent, STRING_SIZE, "%d %d ", getpid(), main_argc - 2);
	for(int i = 2; i < main_argc; i++)
	{
		strcat(message_sent, main_agv[i]);
		strcat(message_sent, " ");
	}

	FILE* f = fopen(PATH_CLIENT, "a");
	if(!f)
	{
		perror("[ERROR]");
		return 2;
	}

	flockfile(f);

	fprintf(f, "%s\n", message_sent);

	funlockfile(f);
	fclose(f);

	return 0;
}


int received_message(const char* path)
{
	char message_received[STRING_SIZE];

	int fd = open(path, O_RDONLY);
	if(fd == -1)
		return -1;

	int error = read(fd, &message_received, STRING_SIZE);
	if(error == -1)
	{
		perror("ERROR]");
		return error;
	}

	error = close(fd);
	if(error)
	{
		perror("ERROR]");
		return -1;
	}	

	int count, gain;
	sscanf(message_received, "%d %d", &count, &gain);

	if(count == -1)
	{
		printf("message_received : Tu as trouve tous numero, tu repars avec %d$!\n", gain);
		return 1;
	}
	if(count)
	{
		printf("message_received : Tu as trouve %d numero, tu repars avec %d$!\n", count, gain);
		return 0;
	}
	else
		printf("message_received : Tu as perdu\n");

	return 0;
}


void unlink_fifo(const char* path)
{
	int error = unlink(path);
	if(error == -1)
	{
		perror("[ERROR]");
		exit(-1);
	}
}


int main(int argc, char** argv)
{
	int error = check_max_argument(argc);
	if(error == 2)
	{
		fprintf(stderr, "[ERROR] There is no ongoing lottery\n");
		return error;
	}
	else if(error == -1)
	{
		fprintf(stderr, "[ERROR] Invalid argument(s)\n");
		return error;
	}

	char path_fifo[STRING_SIZE];
	snprintf(path_fifo, STRING_SIZE, "/tmp/%d.ff", getpid());

	error = mkfifo(path_fifo, 0666);
	if(error == -1)
	{
		perror("[ERROR]");
		return error;
	}

	error = send_message(argc, argv);
	if(error == -1)
	{
		unlink_fifo(path_fifo);
		return error;
	}

	int return_lotttery = 0;
	error = received_message(path_fifo);
	if(error == -1)
	{
		unlink_fifo(path_fifo);
		return error;
	}
	if(error == 1)
		return_lotttery = 1;

	unlink_fifo(path_fifo);

	exit(return_lotttery);
}