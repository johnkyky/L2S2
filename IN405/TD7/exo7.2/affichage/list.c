#include "list.h"




struct LIST* init_list()
{
	struct LIST* res = malloc(sizeof(struct LIST));

	res->size = 0;
	res->first = NULL;

	return res;
}

int free_list(struct LIST** container)
{
	if(!(*container))
		return 1;

	(*container)->size = 0;

	while((*container)->first)
	{
		struct list* buffer = (*container)->first;
		(*container)->first = (*container)->first->next;

		free(buffer->word);
		buffer->word = NULL;
		free(buffer);
		buffer = NULL;
	}

	free(*container);
	*container = NULL;

	return 0;
}

int add_list(struct LIST* container, char* word)
{
	if(!container)
	{
		printf("[ERROR] : add_list\n");
		return 1;
	}

	struct list* res = malloc(sizeof(struct list));
	res->word = malloc(strlen(word) + 1);
	strcpy(res->word, word);
	res->next = NULL;

	if(!container->first)
	{
		container->first = res;
		container->size++;
		return 0;
	}

	struct list* buffer = container->first;

	if(!buffer->next)
	{
		buffer->next = res;
		container->size++;
		return 0;
	}

	while(buffer->next->next)
		buffer = buffer->next;

	buffer->next->next = res;
	container->size++;

	return 0;
}

int print_list(struct LIST* container)
{
	if(!container)
	{
		printf("[ERROR] : print_list\n");
		return 1;
	}

	struct list* buffer = container->first;

	printf("size : %d\n", container->size);
	while(buffer)
	{
		printf("%s\n", buffer->word);
		buffer = buffer->next;
	}

	return 0;
}


int print_i_list(struct LIST* container, const unsigned int i)
{
	if(!container || i >= container->size)
		return 1;

	struct list* buffer = container->first;

	for(unsigned int j = 0; j < i; j++)
		buffer = buffer->next;

	printf("%s\n", buffer->word);

	return 0;
}

unsigned int getSize_list(const struct LIST* container)
{
	return container->size;
}