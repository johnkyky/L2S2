#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


#define PATH "/tmp/envoi_to_affichage"
#define CMD_RESET "reset"
#define CMD_ADD "add"
#define SIZE_WORD_MAX 64



int main(int argc, char** argv)///add | reset
{
	if(argc == 1)
	{
		printf("no arguments\n");
		exit(0);
	}

	pid_t pid;
	int fd;

	if(!strcmp(argv[2], CMD_RESET) && argc == 3)
	{
		pid = atoi(argv[1]);
		printf("reset : pid(%d)\n", pid);

		kill(pid, SIGUSR1);
		mkfifo(PATH, 0666);
		fd = open(PATH, O_CREAT | O_WRONLY);
		write(fd, "0", 1);
		close(fd);
	}
	else if(!strcmp(argv[2], CMD_ADD) && argc == 4)
	{
		pid_t pid = atoi(argv[1]);
		printf("add : pid(%d)\n", pid);

		kill(pid, SIGUSR1);
		char str[96];
		snprintf(str, SIZE_WORD_MAX, "1%s", argv[3]);

		mkfifo(PATH, 0666);
		fd = open(PATH, O_CREAT | O_WRONLY);
		write(fd, str, strlen(str) + 1);
		close(fd);
	}



	return 0;
}