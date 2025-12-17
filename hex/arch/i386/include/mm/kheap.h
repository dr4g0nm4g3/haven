/*
 * kheap.h
 * 	functions and definitions for the kernel heap
 *
 *  Created on: Mar 15, 2009
 *      Author: dragon
 */

#ifndef KHEAP_H_
#define KHEAP_H_

#include <ordered_array.h>

#define KHEAP_START        0xC0000000
#define KHEAP_INITIAL_SIZE 0x100000
#define HEAP_INDEX_SIZE   	0x20000			// size of the data structure that holds the list of holes/blocks
#define HEAP_MAGIC        	0xDEADF00D		// value that each header and footer will contain
#define HEAP_MIN_SIZE     	0x70000

/**
  Size information for a hole/block
**/
typedef struct
{
	unsigned int magic;		// Magic number, used for error checking and identification.
	unsigned char is_hole;   	// 1 if this is a hole. 0 if this is a block.
	unsigned int size;    		// size of the block, including the end footer.
} header_t;

typedef struct
{
	unsigned int magic;     	// Magic number, same as in header_t.
	header_t *header; 			// Pointer to the block header.
} footer_t;

/**
 * data structure representing the heap
 */
typedef struct
{
	ordered_array_t index;			// The ordered array containing the indices of holes/blocks
	unsigned int start_address;	// The start of our allocated space.
	unsigned int end_address;  	// The end of our allocated space. May be expanded up to max_address.
	unsigned int max_address;  	// The maximum address the heap can be expanded to.
} heap_t;

/**
 * Create a new heap.
 *
 * param[in] start memory address of the start of the heap
 * param[in] end memory address of the end of the heap
 * param[in] max max size that the heap can grow to
 * return a pointer to the heap
 */
heap_t * create_heap(unsigned int start, unsigned int end, unsigned int max);

/**
 * Allocates a contiguous region of memory 'size' in size. If page_align==1, it creates that block starting
 * on a page boundary.
 *
 * param[in] size size of memory region to allocate
 * param[in] page_align whether to align the allocated memory to a page boundary
 * param[in] heap pointer to the heap to allocate memory from
 * return a pointer to a contiguous region of memory
 */
void * alloc(unsigned int size, unsigned char page_align, heap_t * heap);

/**
 * Releases a block allocated with 'alloc'.
 *
 * param[in] p pointer to memory region to free
 * param[in] heap pointer to the heap to free the memory from
 */
void free(void * p, heap_t * heap);


#endif /* KHEAP_H_ */
