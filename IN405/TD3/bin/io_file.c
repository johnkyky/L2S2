#include "io_file.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>



IO_FILE IO_open(const char *path, int access)
{
	IO_FILE res;
	if(!path)
	{
		res.desc = -1;
		res.path = NULL;
		res.access = access;
	}

	if(access & O_CREAT)
		res.desc = open(path, access, 0644);
	else
		res.desc = open(path, access);

	res.path = malloc(sizeof(char) * (strlen(path) + 1));
	if(!res.path)
		exit(1);
	strcpy(res.path, path);

	res.access = access;
	
	return res;
}




int IO_close(IO_FILE file)
{
	if(file.desc == -1)
	{
		printf("[ERROR] IO_close -> file descriptor\n");
		return -1;
	}

	int error = close(file.desc);

	if(error)
	{
		perror("[ERROR]");
		return -1;
	}

	free(file.path);

	return 0;
}




int IO_remove(const char *path)
{
	if(!path)
	{
		printf("[ERROR] IO_remove\n");
		exit(1);
	}

	int error = unlink(path);

	if(error)
	{
		perror("[ERROR]");
		return -1;
	}

	return 0;
}




int IO_char_read(IO_FILE file, char *c)
{
	if(file.desc == -1)
	{
		printf("[ERROR] IO_char_read -> file descriptor\n");
		return -1;
	}

	if(!c)
	{
		printf("[ERROR] IO_char_read -> @argument char*\n");
		return -1;
	}	

	ssize_t error = read(file.desc, c, 1);

	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	return error;
}




int IO_char_write(IO_FILE file, const char c)
{
	if(file.desc == -1)
	{
		printf("[ERROR] IO_char_write -> file descriptor\n");
		return -1;
	}

	ssize_t error = write(file.desc, &c, 1);

	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	return 1;
}



int IO_string_read(IO_FILE file, char *string, int maxSize)
{
	if(!string)
	{
		printf("[ERROR] IO_string_read -> @argument string*\n");
		return -1;
	}

	if(file.desc == -1)
	{
		printf("[ERROR] IO_string_read -> file descriptor\n");
		return -1;
	}

	if(maxSize < 0)
	{
		return -1;
	}

	ssize_t error = read(file.desc, string, maxSize);
	//string[maxSize] = '\0';

	if(error == -1)
	{
		perror("[ERROR]");
		return error;
	}

	//string[error + 1] = '\0';

	return error;
}



int IO_string_write(IO_FILE file, const char *string, int size)
{
	if(file.desc == -1)
	{
		printf("[ERROR] IO_string_write -> file descriptor\n");
		return -1;
	}

	if(!string)
	{
		printf("[ERROR] IO_string_write -> @argument string*\n");
		return -1;
	}

	if(size < 0)
	{
		return -1;
	}

	ssize_t error = write(file.desc, string, size);

	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	return error;
}




int IO_int_read(IO_FILE file, int *n)
{
	if(file.desc == -1)
	{
		printf("[ERROR] IO_int_read -> file descriptor\n");
		return -1;
	}

	ssize_t error = -1;
	short test_negatif = 1;
	int buffer_int = 0;
	char buffer_char = ' ';


	while(!isdigit(buffer_char) && error)
	{
		error = read(file.desc, &buffer_char, 1);
		if(error == -1)
		{
			perror("[ERROR]");
			return -1;
		}
		if(buffer_char == '-')
		{
			error = read(file.desc, &buffer_char, 1);
			if(error == -1)
			{
				perror("[ERROR]");
				return -1;
			}
			if(isdigit(buffer_char))
				test_negatif = -1;
		}
	}

	while(isdigit(buffer_char) && error)
	{
		buffer_int = buffer_int * 10 + buffer_char - '0';
		
		error = read(file.desc, &buffer_char, 1);
		if(error == -1)
		{
			perror("[ERROR]");
			return -1;
		}
	}
	
	buffer_int *= test_negatif;
	*n = buffer_int;

	return error;
}




int IO_int_write(IO_FILE file, const int n)
{
	if(file.desc == -1)
	{
		printf("[ERROR] IO_int_write -> file descriptor\n");
		return -1;
	}

	int buffer = n, number_digit = 0;
	while(buffer)
	{
		buffer /= 10;
		number_digit++;
	}

	if(n < 0)
		number_digit++;
	if(!n)
		number_digit = 1;

	char *string = malloc(sizeof(char*) * number_digit + 1);
	snprintf(string, number_digit + 2, "%d", n);

	ssize_t error = write(file.desc, string, number_digit);

	if(error == -1)
	{
		perror("[ERROR]");
		return -1;
	}

	free(string);

	return error;
}