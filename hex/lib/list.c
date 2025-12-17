/*
 * list.c
 *	linked list implementation
 *
 *  Created on: Nov 14, 2009
 *      Author: dragon
 */

#include <list.h>
#include <kmm.h>

void llist_init(List * list, void (*destroy)(void *))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = 0;
	list->tail = 0;
}

void llist_destroy(List * list)
{
	while(llist_size(list) > 0)
	{
		void * data = 0;
		if(llist_rem_next(list, 0, (void **)&data) == 0)
		{
			if(list->destroy)
				list->destroy(data);
		}
	}
}

int llist_ins_next(List * list, ListElem * element, const void * data)
{
	if(list == 0)
		return -1;

	ListElem * new_element = 0;

	// allocate memory for the new element
	new_element = (ListElem *)kmalloc(sizeof(ListElem));

	if(new_element == 0)
		return -1;

	new_element->data = (void *)data;

	if(element == 0)
	{	// insert at the head
		if(llist_size(list) == 0)
			list->tail = new_element;

		// save previous head element and fix the new element to point to it
		new_element->next = list->head;
		// set new element to the head of the list
		list->head = new_element;
	}
	else
	{	// insert after 'element'
		if(element->next == 0)
			list->tail = new_element;

		// insert new_element after 'element'
		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;

	return 0;
}

int llist_rem_next(List * list, ListElem * element, void **data)
{
	if(list == 0)
		return -1;

	if(llist_size(list)  <= 0)
		return -1;

	ListElem * removed_element = 0;

	if(element == 0)
	{	// remove from the head of the linked list
		*data = list->head->data;
		removed_element = list->head;
		list->head = list->head->next;

		// there are no other elements in the list, so set the tail to point to nothing
		if(llist_size(list) == 0)
			list->tail = 0;
	}
	else
	{	// remove the item after 'element'
		if(element->next == 0)
			return -1;

		*data = element->next->data;
		removed_element = element->next;
		element->next = removed_element->next;

		if(element->next == 0)
			list->tail = element;
	}

	if(removed_element)
		kfree((void *)removed_element);

	list->size--;
	return 0;
}

