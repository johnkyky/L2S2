#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 10

pthread_barrier_t barrier;

void* waitting_thread(void* argv)
{
	pthread_barrier_wait(&barrier);
	printf("je suis pas le premier a sortir\n");

	return NULL;
}


void* laster_thread(void* argv)
{
	sleep(1);
	printf("je suis le premier a sortir\n");
	pthread_barrier_wait(&barrier);
	return NULL;
}


int main()
{
	//
	pthread_barrier_init(&barrier, NULL, THREAD_COUNT);

	//
	pthread_t tid[THREAD_COUNT];
	for(int i = 0; i < THREAD_COUNT - 1; i++)
		pthread_create(&tid[i], NULL, waitting_thread, NULL);
	pthread_create(&tid[THREAD_COUNT - 1], NULL, laster_thread, NULL);


	//
	for(int i = 0; i < THREAD_COUNT; i++)
		pthread_join(tid[i], NULL);
	pthread_barrier_destroy(&barrier);

	return 0;
}