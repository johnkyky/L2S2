#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>


void creat_son()
{
	srand(time(NULL));

	int timeout = (rand() % 10) + 1;
	sleep(timeout);

	printf("my son pid : %d | timeout : %d\n", getpid(), timeout);

	exit(0);
}	


int main()
{
	pid_t pid_father = 1;

	for (int i = 0; i < 10; ++i)
	{
		pid_father = fork();
		if(!pid_father)
			creat_son();
		sleep(1);
	}

	for (int i = 0; i < 10; ++i)
		wait(NULL);

	exit(0);
}