#ifndef FONCTIONTHREAD_H
#define FONCTIONTHREAD_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "listPage.h"
#include "fonction.h"

/*
	Initialise thread
	@param tabl array for initiate the thread parameter
	@param number_thread number of threads initialized
	@param tid array of tid
*/
void init_son(struct comunication* tabl, int number_thread, pthread_t* tid);

/*
	Thread main
	@param arg arguments of thread
*/
void* son_fonction(void* arg);

/*
	Destroy memory of thread
	@param tabl array to destroy memory
	@param number_thread number of threads deleted
	@param tid array of tid
*/
void delete_thread(struct comunication* tabl, int n_thread, pthread_t* tid);


#endif