#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>


#define NUM_THREADS 5



void* print_string(void* arg)
{
	char* str = (char*) arg;
	printf("Childsays : '%s'\n", str);
	return NULL;
}

void* print_number(void* args)
{
	int* number = (int*) args;
	printf("Child number's : %d\n", *number);
	return NULL;
}


void* creat_rand_number(void* args)
{
	int* number = malloc(sizeof(int));
	*number = rand() % 100;

	printf("Childsays my random number is : %d\n", *number);

	pthread_exit(number);
}


void* average_tabl_5(void* args)
{
	int* tabl = (int*) args;

	int average = 0;
	for(int i = 0; i < 5; i++)
		average += tabl[i];
	average /= 5;

	printf("Childsays average_5 = %d\n", average);

	return NULL;
}


void* average_tabl_n(void* args)
{
	int* tabl = (int*) args;

	int average = 0;
	for(int i = 1; i < tabl[0]; i++)
		average += tabl[i];
	average /= tabl[0];
	printf("Childsays average_n = %d\n", average);

	return NULL;
}


int main()
{
	srand(getpid());

	//////////////////Creation of tid//////////////////
	pthread_t tid[NUM_THREADS];



	
	//////////////////Creation of threads//////////////////
	pthread_create(&tid[0], NULL, print_string, "Hello World!");

	int rand_number = rand() % 100;
	pthread_create(&tid[1], NULL, print_number, &rand_number);

	pthread_create(&tid[2], NULL, creat_rand_number, NULL);

	int tabl1[5];
	for(int i = 0; i < 5; i++)
		tabl1[i] = rand() % 100;
	pthread_create(&tid[3], NULL, average_tabl_5, &tabl1);


	const int size_tabl = rand() % 20;
	int tabl2[size_tabl + 1];
	tabl2[0] = size_tabl;
	for(int i = 1; i < size_tabl; i++)
		tabl2[i] = rand() % 100;
	pthread_create(&tid[3], NULL, average_tabl_n, &tabl2);


	//////////////////Wait the nd of threads//////////////////
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	int* number_child;
	pthread_join(tid[2], (void **) &number_child);
	printf("My child's random number is : %d\n", *number_child);
	free(number_child);

	pthread_join(tid[3], NULL);

	return 0;
}