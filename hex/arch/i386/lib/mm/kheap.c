/*
 * kheap.c
 * 	implementation of the kernel's heap
 *
 *  Created on: Apr 10, 2009
 *      Author: dragon
 */

#include "kheap.h"

#include <kdbg.h> // for kdbg_log

// end if defined in the linker script
extern unsigned int end;

unsigned int heap_address = (unsigned int)&end;
heap_t * kheap = 0;

// compare function used in the ordered array to determine insertion of the node
static int compare_blocks(const type_t p1, const type_t p2)
{
	header_t * header1 = (header_t *)p1;
	header_t * header2 = (header_t *)p2;
	return (header1->size < header2->size)?1:0;
}

header_t * find_smallest_hole(unsigned int size, heap_t * heap)
{
	unsigned int i = 0;
	while(i < heap->index.size)
	{
		header_t * block = (header_t *)lookup_ordered_array(&heap->index, i);
		if(size <= block->size && block->is_hole == 1)
		{
			kdbg_log("find_smallest_hole - returning memory block:\naddress: 0x%x\nsize: %l\n", block, block->size);
			return block;
		}
		++i;
	}

	return (header_t *)0;
}

heap_t * create_heap(unsigned int start, unsigned int end, unsigned int max)
{
	kdbg_log("create_heap - heap address is 0x%x\n", heap_address);
	// allocate memory for the kernel heap
	heap_t * heap = (heap_t *) alloc(sizeof(heap_t), 0, 0);
	kdbg_log("create_heap - heap_address after alloc(): 0x%x\n", heap_address);
	kdbg_log("create_heap - heap pointer after alloc(): 0x%x\n", heap);

	// create the ordered array that will hold the indices of all available heap memory blocks
	heap->index = place_ordered_array((void *)heap_address, HEAP_INDEX_SIZE, &compare_blocks, 0);

	// place the start of the heap after the array of indices that keeps track of memory blocks
	heap->start_address = heap_address + (sizeof(type_t) * HEAP_INDEX_SIZE);
	heap->end_address = end;
	heap->max_address = max;

	// place one memory hole in the index initially
	header_t * header = (header_t *) heap->start_address;
	header->is_hole = 1;
	header->magic = HEAP_MAGIC;
	header->size = end - start;

	insert_ordered_array(&heap->index, (type_t)header);

	kdbg_log("create_heap - heap structure:\nstart address: 0x%x\nend address: 0x%x\nmaximum address: 0x%x\naddress of ordered array: 0x%x\n",
			heap->start_address, heap->end_address, heap->max_address, &heap->index);

	kdbg_log("create heap - new memory block:\nheader start address: 0x%x\nsize: %l\n",
			header, header->size);

	return heap;
}

void * alloc(unsigned int size, unsigned char page_align, heap_t * heap)
{
	if(heap == 0)
	{	// the heap has not been initialized yet, return a physical address
		kdbg_log("alloc - heap is 0. heap_address is 0x%x. size to allocate is %l\n", heap_address, size);
		unsigned int tmp = heap_address;
		heap_address += size;
		return (void *)tmp;
	}
	else
	{	// allocate a memory block off of the heap
		// search for a free memory block of 'size'
		unsigned int new_size = size + sizeof(header_t) + sizeof(footer_t);
		header_t * smallest_block = find_smallest_hole(new_size, heap);

		if(smallest_block == 0)
		{	// need to allocate more space on the heap
			kdbg_log("alloc - not enough space on the heap. Need to allocate more\n");
		}

		// determine if the hole is larger than needed and we can split it up into a smaller block
		unsigned int overhead = (sizeof(header_t) + sizeof(footer_t));
		if((smallest_block->size - new_size) < overhead)
		{	// the smallest block can't be split up any further
			size += smallest_block->size - new_size;
			new_size = smallest_block->size;
		}

		unsigned int original_size = smallest_block->size;

		// overwrite the existing header
		smallest_block->magic = HEAP_MAGIC;
		smallest_block->is_hole = 0;
		smallest_block->size = new_size;
		footer_t * block_footer = (footer_t *)(smallest_block + sizeof(header_t) + size);
		block_footer->magic = HEAP_MAGIC;
		block_footer->header = smallest_block;

		if(original_size - new_size > 0)
		{	// there is enough space to write another memory block
			header_t * hole = (header_t *)(smallest_block + sizeof(header_t) + sizeof(footer_t) + size);
			hole->magic = HEAP_MAGIC;
			hole->is_hole = 1;
			hole->size = original_size - new_size;
			// the footer starts after the header_t struct and the size of the allocated memory block
			footer_t * hole_footer = (footer_t *)(hole + (original_size - new_size) + sizeof(footer_t));

			if((unsigned int)hole_footer < heap->end_address)
			{	// only add the footer if there is enough space on the heap
				kdbg_log("not enough space at the end of the heap. No footer written\n");
				hole_footer->magic = HEAP_MAGIC;
				hole_footer->header = hole;
			}

			insert_ordered_array(&heap->index, (type_t)hole);

			kdbg_log("alloc - creating new memory block hole with size %l\n", hole->size);
		}

		kdbg_log("alloc - new memory block:\nheader start address: 0x%x\nfooter start address: 0x%x\nsize: %l\n",
				smallest_block, block_footer, smallest_block->size);

		// return pointer to the available memory in between the header_t and footer_t structures
		return (void *)(smallest_block + sizeof(header_t));

	}
	return 0;
}

void free(void * p, heap_t * heap)
{
	header_t * block = (header_t *)(unsigned int)p - sizeof(header_t);
	footer_t * block_footer = (footer_t *)(unsigned int)block + block->size - sizeof(footer_t);

	if(block->magic != HEAP_MAGIC && block_footer->magic != HEAP_MAGIC)
		return;

	// mark the memory block as available to be allocated again
	block->is_hole = 1;
}
