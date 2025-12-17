/*
 * ordered_array.c
 * 	implementation of an ordered array
 *
 *  Created on: Apr 11, 2009
 *      Author: dragon
 */

#include "ordered_array.h"
#include "kmm.h"

int default_lessthan(const type_t p1, const type_t p2)
{
	return (p1 < p2)?1:0;
}

void default_destroy(void * data)
{
	kfree(data);
}

ordered_array_t create_ordered_array(unsigned int max_size, fn_lessthan fp_lessthan, fn_destroy fp_destroy)
{
	ordered_array_t array;
	array.data = (type_t *)kmalloc(max_size * sizeof(type_t));
	array.max_size = max_size;
	array.fp_lessthan = fp_lessthan;
	array.fp_destroy = fp_destroy;
	array.size = 0;

	/* use default functions if none were specified */
	if(fp_lessthan == 0)
		array.fp_lessthan = default_lessthan;

	if(fp_destroy == 0)
		array.fp_destroy = default_destroy;

	return array;
}

ordered_array_t place_ordered_array(void * addr, unsigned int max_size, fn_lessthan fp_lessthan, fn_destroy fp_destroy)
{
	ordered_array_t array;
	array.data = (type_t *)addr;
	array.max_size = max_size;
	array.fp_lessthan = fp_lessthan;
	array.fp_destroy = fp_destroy;
	array.size = 0;

	/* use default functions if none were specified */
	if(fp_lessthan == 0)
		array.fp_lessthan = default_lessthan;

	if(fp_destroy == 0)
		array.fp_destroy = default_destroy;

	return array;
}

void destroy_ordered_array(ordered_array_t * array)
{
	if(array == 0)
		return;

	unsigned int iter = 0;
	while(iter < array->size)
	{
		array->fp_destroy(array->data[iter]);
		iter++;
	}

	kfree(array->data);
	array->data = 0;
	array->fp_destroy = 0;
	array->fp_lessthan = 0;
	array->size = 0;
	array->max_size = 0;
}

type_t lookup_ordered_array(ordered_array_t * array, int index)
{
	if(array == 0)
		return 0;

	if(array->size == 0 || array->size < index)
		return 0;

	return array->data[index];
}

int lookup_index_ordered_array(ordered_array_t * array, type_t data)
{
	if(array == 0)
		return -1;

	int iter = 0;
	while(iter < array->size)
	{
		if(array->data[iter] == data)
			return iter;

		iter++;
	}
	return -1;
}

int insert_ordered_array(ordered_array_t * array, type_t data)
{
	if(array == 0)
		return -1;

	unsigned int iter = 0;
	while(iter < array->size && array->fp_lessthan((const type_t)array->data[iter], (const type_t)data))
	{	// search through ordered array to find point of insertion
		iter++;
	}
	// found, insert data here
	if(array->size == iter)
	{	// insert data at the end
		array->data[array->size++] = data;
	}
	else
	{	// insert in the middle and shift all items
		type_t tmp = array->data[iter];
		array->data[iter] = data;
		while(iter < array->size)
		{	// shift all items down
			iter++;
			type_t tmp2 = array->data[iter];
			array->data[iter] = tmp;
			tmp = tmp2;
		}
		array->size++;
	}
	return 0;
}

int remove_ordered_array(ordered_array_t * array, int index)
{
	if(array == 0)
		return -1;

	while(index < array->size)
	{
		array->data[index] = array->data[index + 1];
		index++;
	}
	array->size--;
	return 0;
}
