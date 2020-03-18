#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <signal.h>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>




void question()
{
	pid_t pid = fork();

	if(!pid)
	{
		for (int i = 0; i < 5; ++i)
		{
			printf("%d\n", i);
			sleep(1);
		}
	}
	else
	{
		sleep(3);

		kill(pid, SIGSTOP);

		sleep(5);

		kill(pid, SIGCONT);

		wait(NULL);
	}
}



int main()
{
	question();

	exit(0);
}