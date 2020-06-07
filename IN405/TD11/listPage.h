#ifndef LISTPAGE_H
#define LISTPAGE_H

#include <stdlib.h>
#include <stdio.h>


struct page
{
	//[born_min, born_max[
	unsigned int born_min;
	unsigned int born_max;
	struct page* nextPage;
};


struct listPage
{
	int size;
	struct page* firstPage;
};

/*
	Initialise a struct listPage

	@return an initialized structure
*/
struct listPage init_listPage();

/*
	Add an unexistant element in list
	@param list the struct list has idited
	@param min param of the struct page to add
	@param max param of the struct page to add
*/
void add_listPage(struct listPage* list, unsigned int min, unsigned int max);

/*
	Add an existant element in list
	@param list the struct list has idited
	@param add struct page to add
*/
void addPage_listPage(struct listPage* list, struct page* add);

/*
	Remove the element at the index index
	@param list the struct list has idited
	@param index index of the element

	@return the element who was remove
*/
struct page* mv_listPage(struct listPage* list, unsigned int index);

/*
	Find the element with param min and max
	@param list the struct list has idited
	@param min param of the struct page to find
	@param max param of the struct page to find

	@return the index of the page finded, else -1
*/
int find_listPage(struct listPage* list, unsigned int min, unsigned int max);

/*
	Remove a struct listPage
	@param list the struct list has idited
*/
void free_listPage(struct listPage* list);

/*
	Print a struct listPage
	@param list the struct list has idited
*/
void print_listPage(struct listPage list);

/*
	Print one element of struct listPage
	@param list the struct list has idited
	@param index index of the element
*/
void print_index_listPage(struct listPage list, int index);


#endif