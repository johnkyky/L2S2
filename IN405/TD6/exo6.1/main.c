#include <unistd.h>
#include <sys/wait.h>


#include <stdlib.h>
#include <stdio.h>



void question1()
{
	pid_t pid = fork();

	
	if(!pid)
	{
		char *argv[] = {"/bin/ps", NULL};
		execv("/bin/ps", argv);
	}
	else
		wait(NULL);

}


void question2()
{
	pid_t pid = fork();

	
	if(!pid)
	{
		char *argv[] = {"/bin/ls", "/home/ugo-btn", NULL};
		execv("/bin/ls", argv);
	}
	else
		wait(NULL);

}



void question3()
{
	pid_t pid[2] = {1, 1};

	for (int i = 0; i < 2; ++i)
		if(pid[i])
			pid[i] = fork();
	

	if(!pid[0] && pid[1])
	{
		char *argv[] = {"/bin/find", "/home/ugo-btn", "-maxdepth", "1", "-type", "d", NULL};
		execv("/bin/find", argv);
	}
	if(!pid[1] && pid[0])
	{
		char *argv[] = {"/bin/find", "/home/ugo-btn", "-maxdepth", "1", "-type", "f", NULL};
		execv("/bin/find", argv);
	}
	if(pid[0] && pid[1])
		for (int i = 0; i < 2; ++i)
			wait(NULL);
}



int main()
{
	question3();
	

	exit(0);
}