#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>


#include "list.h"

#define PATH "/tmp/envoi_to_affichage"
#define SIZE_WORD_MAX 64
#define LOOP 25



struct LIST* container = NULL;



void init_container()
{
	if(!container)
		free_list(&container);
	container = init_list();
	add_list(container, "Bonjour, ceci est un message informatise");

	time_t timestamp = time(NULL);
	struct tm* time_info = localtime(&timestamp);

	char buffer[25];
	sprintf(buffer, "%02d/%02d/%04d-%02d:%02d:%02d", time_info->tm_mday, time_info->tm_mon + 1,
		time_info->tm_year + 1900, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
	
	add_list(container, buffer);
}


void signal_handler(int signo)
{
	char buffer[SIZE_WORD_MAX];
	int fd = open(PATH, 0666);
	read(fd, buffer, SIZE_WORD_MAX);
	close(fd);
	//unlink(PATH);

	printf("-----------message recu : '%s'\n", buffer);

	int mode = buffer[0] - '0';
	if(mode == 0)
		init_container();
	else
	{
		for(int i = 0; i < strlen(buffer); i++)
			buffer[i] = buffer[i + 1];
		add_list(container, buffer);
	}
}


int main()
{
	struct sigaction action;
	action.sa_handler = signal_handler;

	sigaction(SIGUSR1, &action, NULL);


	init_container();

	printf("my pid : %d\n", getpid());

	unsigned int i = 0;
	int done = 0;
	while(done < LOOP)
	{
		print_i_list(container, i);
		i = (i + 1) % getSize_list(container);
		sleep(2);
		done++;
	}

	free_list(&container);

	return 0;
}