/*
 * ordered_array.h
 * 	definition of an ordered array
 *
 *  Created on: Apr 11, 2009
 *      Author: dragon
 */

#ifndef ORDERED_ARRAY_H_
#define ORDERED_ARRAY_H_

/* type of data that will be stored in the array */
typedef void * type_t;

/* typedef for less than function pointer */
typedef int (* fn_lessthan)(const type_t, const type_t);

/* destroy function pointer typedef */
typedef void (* fn_destroy)(void *);

typedef struct
{
	type_t * data;
	unsigned int size;		// number of elements
	unsigned int max_size;	// maximum # of elements allocated to the array
	fn_lessthan fp_lessthan;// pointer to less than function
	fn_destroy fp_destroy;	// pointer to destroy function
} ordered_array_t;

/* create the ordered array */
ordered_array_t create_ordered_array(unsigned int max_size, fn_lessthan fp_lessthan, fn_destroy fp_destroy);

/* create and place the ordered array at a specific address */
ordered_array_t place_ordered_array(void * addr, unsigned int max_size, fn_lessthan fp_lessthan, fn_destroy fp_destroy);

/* destroy the ordered array and all of its elements */
void destroy_ordered_array(ordered_array_t * array);

/* lookup an ordered array item given the index into the array */
type_t lookup_ordered_array(ordered_array_t * array, int index);

/* lookup the index of the data in the array */
int lookup_index_ordered_array(ordered_array_t * array, type_t data);

/* insert an item into the ordered array */
int insert_ordered_array(ordered_array_t * array, type_t data);

/* remove an item from the ordered array at the given index */
int remove_ordered_array(ordered_array_t * array, int index);


#endif /* ORDERED_ARRAY_H_ */
