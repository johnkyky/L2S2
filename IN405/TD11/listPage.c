#include "listPage.h"


struct listPage init_listPage()
{
	struct listPage res;

	res.size = 0;
	res.firstPage = NULL;

	return res;
}


void add_listPage(struct listPage* list, unsigned int min, unsigned int max)
{
	struct page* buffer = malloc(sizeof(struct page));
	buffer->born_min = min;
	buffer->born_max = max;
	buffer->nextPage = list->firstPage;
	list->firstPage = buffer;
	list->size++;
}


void addPage_listPage(struct listPage* list, struct page* add)
{
	add->nextPage = list->firstPage;
	list->firstPage = add;
	list->size++;
}


struct page* mv_listPage(struct listPage* list, unsigned int index)
{
	if(index >= list->size)
		return NULL;

	struct page* res;;

	if(index == 0)
	{
		res = list->firstPage;
		list->firstPage = res->nextPage;
	}
	else
	{
		struct page* buffer = list->firstPage;

		for(int i = 0; i < index - 1; i++)
			buffer = buffer->nextPage;

		res = buffer->nextPage;

		buffer->nextPage = res->nextPage;
	}
	list->size--;

	res->nextPage = NULL;
	return res;
}


int find_listPage(struct listPage* list, unsigned int min, unsigned int max)
{
	int index = 0;

	struct page* buffer = list->firstPage;
	
	while(buffer)
	{
		if(buffer->born_min == min && buffer->born_max == max)
			return index;

		buffer = buffer->nextPage;
		index++;
	}

	return -1;
}


void free_listPage(struct listPage* list)
{
	while(list->firstPage)
	{
		struct page* buffer = list->firstPage;
		list->firstPage = buffer->nextPage;
		free(buffer);
		buffer = NULL;
		list->size--;
	}
}


void print_listPage(struct listPage list)
{
	printf("listPage.size = %d\n", list.size);

	struct page* buffer = list.firstPage;

	if(!buffer)
		printf("listPage empty\n");

	while(buffer)
	{
		printf("%d %d\n", buffer->born_min, buffer->born_max);
		buffer = buffer->nextPage;
	}
}


void print_index_listPage(struct listPage list, int index)
{
	if(list.size <= index)
		return;

	struct page* buffer = list.firstPage;
	int i = 0;

	while(i < index && buffer)
	{
		buffer = buffer->nextPage;
		i++;
	}

	printf("%d %d\n", buffer->born_min, buffer->born_max);
}
