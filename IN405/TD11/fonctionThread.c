#include "fonctionThread.h"


void init_son(struct comunication* tabl, int n_thread, pthread_t* tid)
{
	for(int i = 0; i < n_thread; i++)
		pthread_create(&tid[i], NULL, son_fonction, &tabl[i]);
}


void* son_fonction(void* arg)
{
	struct comunication* mess = (struct comunication*) arg;

	for(unsigned int request = 0; request < mess->number_request; request++)
	{
		pthread_mutex_lock(&(mess->local_mutex));
		mess->adress[0] = rand() % ((mess->max_val_adress - 1) + 1);
		pthread_cond_wait(&(mess->local_cond), &(mess->local_mutex));

		mess->adress[1] = 0;
		pthread_mutex_unlock(&(mess->local_mutex));
	}

	return NULL;
}


void delete_thread(struct comunication* tabl, int n_thread, pthread_t* tid)
{
	for(int i = 0; i < n_thread; i++)
	{
		pthread_mutex_destroy(&tabl[i].local_mutex);
		pthread_cond_destroy(&tabl[i].local_cond);
		pthread_join(tid[i], NULL);
	}

}