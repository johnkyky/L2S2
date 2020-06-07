#ifndef FONCTION_H
#define FONCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "listPage.h"



struct comunication
{
	unsigned int adress[2];
	unsigned int number_request;
	unsigned int max_val_adress;
	pthread_mutex_t local_mutex;
	pthread_cond_t local_cond;
	unsigned int hit;
};

/*
	Initialise struct comunication
	@param tabl array of struct comunication to edit
	@param n_thread number of thread
	@param n_request number of request
	@param n_page number of frame
	@param s_page size of frame
*/
void init_comunication(struct comunication* tabl, int n_thread, int n_request, int n_page, int s_page);

/*
	Initialise the disk 
	@param disque struct listPage edited
	@param n_page number of frame
	@param s_page size of one frame
*/
void init_disque(struct listPage* disque, int n_page, int s_page);

/*
	Initialise the ram 
	@param ram struct listPage edited
	@param disque struct listPage for init ram
	@param n_frame size of the ram
*/
void init_ram(struct listPage* ram, struct listPage* disque, int n_frame);

/*
	LRU algorithme
	@param adress physical adress
	@param disque simulate disk
	@param ram simulate ram
	@param size_page size of frame
*/
int LRU(int adress, struct listPage* disque, struct listPage* ram, int size_page, int* hit);

/*
	Load the config file
	@param filename
	@param n_frame number of frame
	@param s_page size of one page
	@param n_page number of page
	@param n_thread number of thread
	@param n_request number of request
*/
void load_config(char* filename, int* n_frame, int* s_page, int* n_page, int* n_thread, int* n_request);


#endif