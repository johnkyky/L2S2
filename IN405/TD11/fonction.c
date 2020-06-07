#include "fonction.h"


void init_comunication(struct comunication* tabl, int n_thread, int n_request, int n_page, int s_page)
{
	for(int i = 0; i < n_thread; i++)
	{
		tabl[i].adress[0] = 0;
		tabl[i].adress[1] = 0;
		tabl[i].number_request = n_request;
		tabl[i].max_val_adress = n_page * s_page;
		pthread_mutex_init(&tabl[i].local_mutex, NULL);
		pthread_cond_init(&tabl[i].local_cond, NULL);
		tabl[i].hit = 0;
	}
}



void init_disque(struct listPage* disque, int n_page, int s_page)
{
	for(int i = 0; i < n_page; i++)
		add_listPage(disque, i * s_page, (i + 1) * s_page);
}



void init_ram(struct listPage* ram, struct listPage* disque, int n_frame)
{
	for(int i = 0; i < n_frame; i++)
		addPage_listPage(ram, mv_listPage(disque, 0));
}



int LRU(int adress, struct listPage* disque, struct listPage* ram, int size_page, int* hit)
{
	int born;
	born = (adress / size_page) * size_page;
	
	int test_ram = find_listPage(ram, born, born + size_page);
	
	if(test_ram == -1)
	{
		int index = find_listPage(disque, born, born + size_page);
		struct page* mvRam = mv_listPage(disque, index);
		struct page* mvDisque = mv_listPage(ram, ram->size - 1);

		if(!mvRam || !mvDisque)
			return -1;

		addPage_listPage(ram, mvRam);
		addPage_listPage(disque, mvDisque);
	}
	else
	{
		addPage_listPage(ram, mv_listPage(ram, test_ram));
		*hit = 1;
	}

	return (adress % size_page);
}



void load_config(char* filename, int* n_frame, int* s_page, int* n_page, int* n_thread, int* n_request)
{
	FILE* file = fopen(filename, "r");

	fscanf(file, "%d %d %d %d %d", n_frame, s_page, n_page, n_thread, n_request);

	if(*n_frame < 1 || *s_page < 1 || *n_page < 1 || *n_thread < 1 || *n_request < 1 || *n_frame >= *n_page)
		exit(1);

	fclose(file);
}