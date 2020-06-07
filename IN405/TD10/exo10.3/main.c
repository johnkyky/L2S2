#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 10

void* fonction_thread(void* argv)
{
	printf("%d\n", *(int*)argv);
	return NULL;
}


int main()
{
	//
	pthread_t tid[THREAD_COUNT];
	int short_tid[THREAD_COUNT];
	for(int i = 0; i < THREAD_COUNT; i++)
	{
		short_tid[i] = i;
		pthread_create(&tid[i], NULL, fonction_thread, &short_tid[i]);
	}

	FILE* f = fopen("./fgh", "r");

	if(!f)
		printf("fichier existe pas\n");
	else
		fclose(f);


	//
	for(int i = 0; i < THREAD_COUNT; i++)
		pthread_join(tid[i], NULL);

	return 0;
}