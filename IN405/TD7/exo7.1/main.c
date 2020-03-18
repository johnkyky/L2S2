#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


#define SIZE_MAX 16

	
/*int anonymous()
{
	int gate[2];

	if(pipe(gate))
	{
		perror("[ERROR]");
		return 1;
	}

	int pid = fork();

	if(pid > 0)
	{
		close(gate[0]);
		char word[] = "Hello World!";

		printf("Message envoye : '%s'\n", word);

		write(gate[1], word, sizeof(word));

		close(gate[0]);

		wait(NULL);
	}
	else if(pid == 0)
	{
		close(gate[1]);

		char word[SIZE_MAX];
		read(gate[0], word, SIZE_MAX);

		printf("Message recu : '%s'\n", word);

		close(gate[0]);
	}
	else
	{
		perror("[ERROR]");
		return 1;
	}
	
	return 0;
}*/


int fifo()
{
	char path[] = "/tmp/test_fifo";
	int fd;


	int pid = fork();

	if(pid > 0)
	{
		const char word[] = "Hello World!";
		printf("Message envoye : '%s'\n", word);

		mkfifo(path, 0666);

		fd = open(path, O_WRONLY);

		write(fd, word, sizeof(word));

		close(fd);

		wait(NULL);
	}
	else if(pid == 0)
	{
		char word[SIZE_MAX];

		fd = open(path, O_RDONLY);

		read(fd, word, SIZE_MAX);

		close(fd);

		printf("Message recu : '%s'\n", word);

		unlink(path);
	}
	else
	{
		perror("[ERROR]");
		return 1;
	}
	
	return 0;
}


int main()
{
	//anonymous();
	fifo();


	return 0;
}