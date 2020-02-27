#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


#define SIZE_PATH 512



void get_type(const char* path)
{
	struct stat statbuf;

	lstat(path, &statbuf);



}


void get_permission(const char* path)
{

}

void get_proprietere(const char* path)
{
	
}


void get_size(const char* path)
{
	struct stat statbuf;

	lstat(path, &statbuf);

	printf(" %ld ", statbuf.st_size);
}


void get_info(const char* path)
{
	get_permission(path);
	get_type(path);
	get_proprietere(path);
	get_size(path);
}



int main(int argc, char** argv)
{
	printf("demo\n");

	char path[SIZE_PATH];

	if(!getcwd(path, SIZE_PATH))
	{
		perror("[ERROR]");
		exit(1);
	}

	printf("path : %s\n\n", path);

	DIR* dir = NULL;
	if(!(dir = opendir(path)))
	{
		perror("[ERROR]");
		exit(1);
	}

	struct dirent* readfile = NULL;
	while((readfile = readdir(dir)))
	{
		if(readfile->d_name[0] == '.')
			continue;

		char buffer[2 * SIZE_PATH];
		strcat(buffer, path);
		get_info(buffer);
		printf("%s\n", readfile->d_name);
	}





	/*if(closedir(dir) == -1)
	{
		perror("[ERROR]");
		exit(1);
	}*/

	return 0;
}