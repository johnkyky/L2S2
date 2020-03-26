#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


int creat_file()
{
	mkdir("/tmp/million", 0777);
	creat("/tmp/million/.config", 0666);
	creat("/tmp/million/client.ff", 0666);

	return 0;
}

int remove_file()
{
	unlink("/tmp/million/client.ff");
	unlink("/tmp/million/.config");
	rmdir("/tmp/million");

	return 0;
}


int load_max_argument(const char* path)
{
	char max_argument = 0;

	int fd = open(path, O_RDONLY);
	read(fd, &max_argument, sizeof(int));
	close(fd);

	printf("max_argument = %c\n", max_argument);

	return max_argument - '0';
}

int load_winning_number(int* win_tabl, const int max_arg, const char* path)
{
	FILE* file = fopen(path, "r");

	fscanf(file, " %d", &win_tabl[0]);
	for(int i = 0; i < max_arg; i++)
		fscanf(file, " %d", &win_tabl[i]);

	fclose(file);

	return 0;
}


int write_config(const int max_arg)
{
	int fd = open("/tmp/million/.config", O_WRONLY | O_CREAT | O_TRUNC);
	write(fd, &max_arg, sizeof(int));
	close(fd);

	return 0;
}



FILE* open_file_read()
{
	FILE* f = fopen("/tmp/million/client.ff", "r");
	if(!f)
	{
		printf("f = NULL\n");
		exit(0);
	}

	return f;
}

int empty_file(FILE* f)
{
	f = fopen("/tmp/million/client.ff", "w");

	return 0;
}


int split_value(int* client_tabl, char* string)
{
	char d[] = " ";
	char *p = strtok(string, d);
	int val = 0;
	while(p != NULL)
	{
	    client_tabl[val] = atoi(p);
	    val++;
	    p = strtok(NULL, d);
	}

	return 0;
}


int verif_value(const int max_arg, int* win_tabl, int* client_tabl)
{
	int count = 0;
	for(int i = 0; i < max_arg; i++)
	{
		for(int j = 2; j < client_tabl[1] + 2; j++)
		{
			if(win_tabl[i] == client_tabl[j])
				count++;
		}
	}

	printf("count -> %d\n----------------------------\n", count);///a supprimer

	return count;
}


int send_message(const int pid, const int count)
{
	char path_fifo[64];
	snprintf(path_fifo, 64, "/tmp/million/%d.ff", pid);

	char message[64];
	snprintf(message, 64, "tu as trouve %d", count);
	int fd = open(path_fifo, O_WRONLY);
	write(fd, message, 64);
	close(fd);

	return 0;
}


int main(int argc, char** argv)
{
	creat_file();

	int max_argument = load_max_argument(argv[1]);

	int winning_number[max_argument];
	load_winning_number(winning_number, max_argument, argv[1]);

	for(int i = 0; i < max_argument; i++)///a supprimer
		printf(">%d ", winning_number[i]);///a supprimer
	printf("\n");///a supprimer

	write_config(max_argument);

	char* buffer = NULL;
	size_t len = 0;

	bool done = true;
	while(done)
	{
		FILE* file = open_file_read();

		if(!(getline(&buffer, &len, file) == EOF))
		{
			printf("----------------------------\n%s\n", buffer);///a supprimer

			int client_number[max_argument + 2];

			split_value(client_number, buffer);

			for(int i = 0; i < client_number[1] + 2; i++)///a supprimer
				printf("-> %d\n", client_number[i]);///a supprimer

			int count = verif_value(max_argument, winning_number, client_number);

			if(count)
				done = false;

			send_message(client_number[0], count);

			fclose(file);
			empty_file(file);
		}

		if(buffer == NULL)
			free(buffer);

		fclose(file);
	}

	remove_file();

	return 0;
}