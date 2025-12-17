/*
 * kmm.c
 * 	implementation of the kernel memory manager
 *
 *  Created on: Apr 10, 2009
 *      Author: dragon
 */

#include "kheap.h"

#include <kdbg.h> // for kdbg_log

// points to the start of the heap
extern unsigned int heap_address;

// define global heap variable
extern heap_t * kheap;

void kmm_init()
{
	kheap = create_heap(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0xFFFFF);
	kdbg_log("kmm_init() - global kheap pointer: 0x%x\n", kheap);
}

void * kmalloc(unsigned int size)
{
	if(kheap == 0)
		return 0;

	return alloc(size, 0, kheap);
}

void kfree(void * p)
{
	if(kheap != 0 && p != 0);
		free(p, kheap);
}

void kdbg_printmem()
{
	unsigned int i = 0;
	unsigned int iNumFreeBlocks = 0;
	unsigned int iMaximumFreeBlockSize = 0;
	unsigned int iMaximumFreeBlockSizeIdx = 0;
	unsigned int iNumAllocatedBlocks = 0;
	unsigned int iMaximumAllocatedBlockSize = 0;
	unsigned int iMaximumAllocatedBlockSizeIdx = 0;

	while(kheap && i < kheap->index.size)
	{
		header_t * data = (header_t *)lookup_ordered_array(&kheap->index, i);

		// generate statistical information about the memory landscape
		if(data->is_hole)
		{
			if(data->size >= iMaximumFreeBlockSize)
			{
				iMaximumFreeBlockSize = data->size;
				iMaximumFreeBlockSizeIdx = i;
			}
			iNumFreeBlocks++;
		}
		else
		{
			if(data->size >= iMaximumAllocatedBlockSize)
			{
				iMaximumAllocatedBlockSize = data->size;
				iMaximumAllocatedBlockSizeIdx = i;
			}
			iNumAllocatedBlocks++;
		}

		//kdbg_log("\nheader at index %d:\nmagic: 0x%x\nis hole? %s\nsize: %l\n", i, data->magic, (data->is_hole == 1)?"yes":"no", data->size);
		++i;
	}

	kdbg_log("******************** Heap Diagnostics ************************\n");
	kdbg_log("Number of free blocks:		%d\n", iNumFreeBlocks);
	kdbg_log("Number of allocated blocks:	%d\n\n", iNumAllocatedBlocks);
	kdbg_log("Largest free block:			0x%d (heap index %d)\n", iMaximumFreeBlockSize, iMaximumFreeBlockSizeIdx);
	kdbg_log("Largest allocated block:		0x%d (heap index %d)\n", iMaximumAllocatedBlockSize, iMaximumAllocatedBlockSizeIdx);
	kdbg_log("******************* End Heap Diagnostics *********************\n");
}
