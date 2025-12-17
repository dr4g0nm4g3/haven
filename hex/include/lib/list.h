/*
 * list.h
 * 	interface for a linked list implementation
 *
 *  Created on: Nov 14, 2009
 *      Author: dragon
 */

#ifndef LIST_H_
#define LIST_H_

/* single element of a linked list */
typedef struct ListElem_
{
	void * data;
	struct ListElem_ * next;
} ListElem;

/* linked list structure */
typedef struct List_
{
	int size;

	void (* destroy)(void * data);

	ListElem * head;
	ListElem * tail;
} List;

/**
 * intialize a new linked list
 *
 * @param[in] list List to initialize
 * @param[in] (*destroy) pointer to a function which handles deleting the data in the linked list
 */
void llist_init(List * list, void (*destroy)(void *));

/**
 * destroy the linked list
 *
 * @param[in] list linked list to destroy
 */
void llist_destroy(List * list);

/**
 * insert a new element into the linked list
 *
 * @param[in] list linked list to insert the element into
 * @param[in] element insert the new element after this element.
 * 			A value of NULL inserts the new element at the head of the linked list
 * @param[in] data data that will represent the new element in the linked list
 * @return 0 if successfully inserted
 * @return -1 for failure
 */
int llist_ins_next(List * list, ListElem * element, const void * data);

/**
 * remove an element from the linked list
 *
 * @param[in] list linked list to remove the element from
 * @param[in] element remove the element after this element.
 * 			A value of NULL removes the element at the head of the linked list
 * @param[out] data data that was removed from the linked list
 * @return 0 if successfully removed
 * @return -1 for failure
 */
int llist_rem_next(List * list, ListElem * element, void **data);

/* returns the number of the elements in the linked list */
#define llist_size(list) ((list)->size)

/* retrieve the element at the head of the linked list */
#define llist_head(list) ((list)->head);

/* retrieve the element at the tail of the linked list */
#define llist_tail(list) ((list)->tail);

/* returns true if the element is at the head, otherwise it returns false */
#define llist_is_head(list, element) (((element) == (list)->head) ? 1: 0)

/* returns true if the element is at the tail, otherwise it returns false */
#define llist_is_tail(list, element) (((element)->next == NULL) ? 1: 0)

/* return the data of the element in the list */
#define llist_data(element) ((element)->data)

/* return the next element in the list */
#define llist_next(element) ((element)->next)


#endif /* LIST_H_ */
