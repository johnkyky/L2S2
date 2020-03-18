#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <signal.h>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>

int i;


void sah(int val)
{
	printf("debug : %d\n", i);
}



void question()
{
	pid_t pid = fork();

	if(!pid)
	{
		struct sigaction action;
		action.sa_handler = sah;
		action.sa_flags = SA_ONSTACK;

		sigaction(SIGUSR1, &action, NULL);

		for (i = 0; i < 12; ++i)
		{
			printf("%d\n", i);
			sleep(1);
		}
	}
	else
	{
		sleep(3);
		kill(pid, SIGUSR1);
		sleep(5);
		kill(pid, SIGUSR1);
		sleep(8);
		kill(pid, SIGUSR1);

		wait(NULL);
	}
}



int main()
{
	question();

	exit(0);
}