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


#define PATH_CONFIG "/tmp/.config"
#define PATH_CLIENT "/tmp/client.ff"
#define STRING_SIZE 64


int creat_file()
{
	if(creat(PATH_CONFIG, 0666) < 0)
	{
		perror("[ERROR]");
		return -1;
	}
	if(creat(PATH_CLIENT, 0666) < 0)
	{
		perror("[ERROR]");
		return -1;
	}

	return 0;
}

int remove_file()
{
	if(unlink(PATH_CLIENT))
	{
		perror("[ERROR]");
		return -1;
	}
	if(unlink(PATH_CONFIG))
	{
		perror("[ERROR]");
		return -1;
	}

	return 0;
}


int load_max_argument(const char* path)
{
	char max_argument = 0;

	int fd = open(path, O_RDONLY);
	if(fd == -1)
		return -1;
	
	int error = read(fd, &max_argument, sizeof(int));
	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	if(close(fd) == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	return max_argument - '0';
}


int load_winning_number_gain(int* win_tabl, int* gain_tabl, const int max_arg, const char* path)
{
	FILE* file = fopen(path, "r");
	if(!file)
	{
		perror("[ERROR]");
		return -1;
	}

	fscanf(file, " %d", &win_tabl[0]);
	for(int i = 0; i < max_arg; i++)
		fscanf(file, " %d", &win_tabl[i]);
	for(int i = max_arg - 1; i > -1; i--)
		fscanf(file, " %d %d", &gain_tabl[i], &gain_tabl[i]);

	fclose(file);

	return 0;
}


int write_config(const int max_arg)
{
	int fd = open(PATH_CONFIG, O_WRONLY | O_CREAT | O_TRUNC);
	if(fd == -1)
	{
		perror("[ERROR]");
		return -1;
	}
	int error = write(fd, &max_arg, sizeof(int));
	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	error = close(fd);
	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	return 0;
}



FILE* open_file_read()
{
	FILE* f = fopen(PATH_CLIENT, "r");
	if(!f)
	{
		printf("f = NULL\n");
		exit(0);
	}

	return f;
}


int read_line(FILE* f, char* buffer)
{
	char letter;
	int count = 0;

	letter = fgetc(f);
	if(letter == EOF)
	{
		if(fseek(f, ftell(f) + 1, SEEK_SET))
			return -1;
		if(fseek(f, ftell(f) - 1, SEEK_SET))
			return -1;
	}

	while(letter != '\n' && letter != EOF)
	{
		buffer[count] = letter;
		count++;
		letter = fgetc(f);
	}
	buffer[count] = '\0';

	if(letter == EOF)
		return 1;

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

	return count;
}


int send_message(const int pid, const int count, const int gain)
{
	char path_fifo[STRING_SIZE];
	snprintf(path_fifo, STRING_SIZE, "/tmp/%d.ff", pid);

	char message[STRING_SIZE];
	snprintf(message, STRING_SIZE, "%d %d", count, gain);
	int fd = open(path_fifo, O_WRONLY);
	if(fd == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	int error = write(fd, message, STRING_SIZE);
	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	error = close(fd);
	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	return 0;
}


int main(int argc, char** argv)
{
	if(creat_file())
		return -1;

	int max_argument = load_max_argument(argv[1]);
	if(max_argument == -1)
	{
		remove_file();
		return -1;
	}

	int winning_number[max_argument];
	int gain[max_argument];
	if(load_winning_number_gain(winning_number, gain, max_argument, argv[1]) == -1)
	{
		remove_file();
		return -1;
	}

	if(write_config(max_argument))
	{
		remove_file();
		return -1;
	}

	char buffer[STRING_SIZE];
	bool done = true;

	FILE* f = open_file_read();
	while(done)
	{
		int error = read_line(f, buffer);
		if(error == -1)
		{
			remove_file();
			return error;
		}
		
		if(buffer[0] != '\0')
		{
			int client_number[max_argument + 2];

			split_value(client_number, buffer);

			int count = verif_value(max_argument, winning_number, client_number);

			if(count == max_argument)
			{
				done = false;
				count = -1;
			}

			error = send_message(client_number[0], count, gain[count - 1]);
			if(error == -1)
			{
				remove_file();
				return error;
			}
		}
		else
			sleep(1); 
	}

	fclose(f);

	if(remove_file())
		return -1;

	return 0;
}