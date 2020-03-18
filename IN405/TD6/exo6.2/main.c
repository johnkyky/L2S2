#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>

#include <stdlib.h>
#include <stdio.h>




void question()
{
	pid_t pid = fork();

	if(!pid)
	{
		char *arguments[] = {"/bin/ls", "-R", "/", NULL};
		execv("/bin/ls", arguments);
	}
	else
		wait(NULL);

	struct tms time;
	times(&time);

	printf("time = %lf\n", (float)time.tms_cstime / sysconf(_SC_CLK_TCK));
}



int main()
{
	question();

	exit(0);
}