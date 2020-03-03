#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/*int main()
{
	int tube[2];
	pipe(tube);

	pid_t pid = fork();

	if(pid)
	{
		close(tube[1]);
		printf("Hello World! -> pere\n");
		printf("pid : %d -> pere\n", getpid());

		int alea_int_pere;

		read(tube[0], &alea_int_pere, sizeof(int));
		printf("alea_int = %d -> pere\n", alea_int_pere);

		wait(NULL);
	}
	else
	{
		close(tube[0]);
		printf("Hello World! -> fils\n");
		printf("pid : %d | ppid : %d -> fils\n", getpid(), getppid());
		
		int alea_int_fils = rand() % 50;
		printf("alea_int = %d -> fils\n", alea_int_fils);
		write(tube[1], &alea_int_fils, sizeof(int));
	}

	exit(0);
}*/



int main()
{
	pid_t pid = fork();

	if(pid)
	{
		printf("Hello World! -> pere\n");
		printf("pid : %d -> pere\n", getpid());

		int alea_int_pere;

		wait(&alea_int_pere);

		printf("alea_int = %d -> pere\n", WEXITSTATUS(alea_int_pere));
	}
	else
	{
		printf("Hello World! -> fils\n");
		printf("pid : %d | ppid : %d -> fils\n", getpid(), getppid());
		
		int alea_int_fils = rand() % 50;
		printf("alea_int = %d -> fils\n", alea_int_fils);

		exit(alea_int_fils);
	}

	exit(0);
}