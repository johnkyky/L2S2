#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "listPage.h"
#include "fonction.h"
#include "fonctionThread.h"



int main()
{
	srand(getpid());

	int number_frame, size_page, number_page, number_thread, number_request;
	load_config("config", &number_frame, &size_page, &number_page, &number_thread, &number_request);

	struct comunication comunication_tabl[number_thread];
	init_comunication(comunication_tabl, number_thread, number_request, number_page, size_page);

	pthread_t tid[number_thread];
	init_son(comunication_tabl, number_thread, tid);

	struct listPage ramPage = init_listPage();
	struct listPage disquePage = init_listPage();

	init_disque(&disquePage, number_page, size_page);

	init_ram(&ramPage, &disquePage, number_frame);

	int done = 0;
	while(done < number_request * number_thread)
	{
		for(int i = 0; i < number_thread; i++)
		{
			char do_changement = 0;
			pthread_mutex_lock(&comunication_tabl[i].local_mutex);

			if(comunication_tabl[i].adress[0] != 0)
			{
				int test_hit = 0;
				comunication_tabl[i].adress[1] = LRU(comunication_tabl[i].adress[0], &disquePage, &ramPage, size_page, &test_hit);
				comunication_tabl[i].adress[0] = 0;
				do_changement = 1;

				if(test_hit)
					comunication_tabl[i].hit += 1;
			}

			if(do_changement == 1)
			{
				pthread_cond_signal(&comunication_tabl[i].local_cond);
				done++;
			}
			pthread_mutex_unlock(&comunication_tabl[i].local_mutex);
		}
	}

	delete_thread(comunication_tabl, number_thread, tid);
	free_listPage(&ramPage);
	free_listPage(&disquePage);

	for(int i = 0; i < number_thread; i++)
		printf("Le thread %d a fait %f%c de hit\n", i, ((float)comunication_tabl[i].hit / (float)number_request) * 100, 37);

	return 0;
}