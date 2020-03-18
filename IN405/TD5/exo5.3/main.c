#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>


#define m 2
#define n 4



void question5()
{
	pid_t pid;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
		{
			pid = fork();
			if(!pid)
			{
				printf("getpid() : %d [%d,%d]\n", getpid(), i, j);
				sleep(1);
				exit(0);
			}
		}

	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			wait(NULL);
}


void question6()
{
	pid_t pid;
	for (int i = 0; i < m; ++i)
	{
		pid = fork();

		if(!pid)
		{
			printf("je suis fils\n");

			for (int j = 0; j < n; ++j)
			{
				pid = fork();
				if(!pid)
				{
					printf("je suis petit fils\n");
					exit(0);
				}
			}

			for (int i = 0; i < n; ++i)
				wait(NULL);

			exit(0);
		}
	}

	for (int i = 0; i < m; ++i)
		wait(NULL);
}


void question7(int mm)
{
	if(mm >= 0)
	{
		pid_t pid;
		for (int i = 0; i < n; ++i)
		{
			pid = fork();
			if(!pid)
			{
				question7(--mm);
				exit(0);
			}
		}

		for (int i = 0; i < n; ++i)
			wait(NULL);
	}
}



int main()
{
	//question5();
	//question6();
	question7(m);



	exit(0);
}