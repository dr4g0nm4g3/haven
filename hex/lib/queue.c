/*
 * queue.c
 * 	implementation of a queue
 *
 *  Created on: Nov 14, 2009
 *      Author: dragon
 */

#include <queue.h>


void queue_init(Queue * q, void (*destroy)(void *))
{
	llist_init(q, destroy);
}

void queue_destroy(Queue * q)
{
	llist_destroy(q);
}

int queue_enqueue(Queue * q, const void * data)
{
	return llist_ins_next(q, 0, data);
}

int queue_dequeue(Queue * q, void ** data)
{
	return llist_rem_next(q, 0, data);
}

void * queue_peek(const Queue * q)
{
	if(q)
		return q->head->data;

	return (void *)0;
}

int queue_size(Queue * q)
{
	if(q)
		return llist_size(q);

	return 0;
}
