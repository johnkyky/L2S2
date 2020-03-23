#include <stdlib.h>
#include <stdio.h>

#include <string.h>


struct list
{
	char* word;
	struct list* next;
};

struct LIST
{
	unsigned int size;
	struct list* first;
};


struct LIST* init_list();

int free_list(struct LIST** container);

int add_list(struct LIST* container, char* word);

int print_list(struct LIST* container);

int print_i_list(struct LIST* container, const unsigned int i);

unsigned int getSize_list(const struct LIST* container);