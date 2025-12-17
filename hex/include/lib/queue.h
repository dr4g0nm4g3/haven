/*
 * queue.h
 * 	interface for a queue, which stores data in a FIFO (first in, first out) order
 *
 *  Created on: Nov 14, 2009
 *      Author: dragon
 */

#ifndef QUEUE_H_
#define QUEUE_H_

// queue is built upon the linked list data structure
#include <list.h>

typedef List Queue;

/**
 * initialize a queue
 *
 * @param[in] q pointer to a queue to intialize
 * @param[in] destroy function pointer to a method to free the data inside the queue
 */
void queue_init(Queue * q, void (*destroy)(void *));

/**
 * destroy the queue and de-allocate all the memory contained within
 *
 * @param[in] q queue to destroy
 */
void queue_destroy(Queue * q);

/**
 * enqueue an element
 *
 * @param[in] q queue to enqueue the element
 * @param[in] data element's data to enqueue
 * @return 0 if successfully enqueued
 * @return -1 for failure
 */
int queue_enqueue(Queue * q, const void * data);

/**
 * dequeue an element
 *
 * @param[in] q queue to deque from
 * @param[in] data pointer to the element's data that was dequeued
 * @return 0 if successfully dequeued
 * @return -1 for failure
 */
int queue_dequeue(Queue * q, void ** data);

/**
 * peek at the data stored in the first element in the queue
 *
 * @param[in] q Queue to peek from
 * @return a pointer to the first element's data
 * @return NULL if the queue is empty
 */
void * queue_peek(const Queue * q);

/**
 * return the number of elements in the queue
 *
 * @param[in] q Queue to get the number of elements from
 * @return the number of elements in the queue
 */
int queue_size(Queue * q);


#endif /* QUEUE_H_ */
