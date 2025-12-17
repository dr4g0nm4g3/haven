/*
 * kmm_unittest.c
 *
 *  Created on: Sep 24, 2011
 *      Author: dragon
 */

#include "kmm_unittest.h"

#include <kmm.h>
#include "ordered_array.h"

#include <console.h>

#include <serial.h>

#include <kdbg.h>

void test_kmm()
{
	// Test 1
	//	Create an array which will hold heap allocated memory blocks
	//	Then destroy the array. All allocated memory blocks should be
	//	freed
	ordered_array_t allocated_memory = create_ordered_array(1000, 0, 0);
	int i = 0;
	int iMaxAllocations = 1000;
	for(; i < iMaxAllocations; ++i)
	{
		int size = i++;
		void * testdata = kmalloc(size);

		if(testdata != 0)
			insert_ordered_array(&allocated_memory, (type_t)testdata);
		else
			kdbg_log("failed to allocated memory block of size %d", size);

	}

	destroy_ordered_array(&allocated_memory);

	kdbg_printmem();

	// Test 2
	//	Test allocating and freeing memory blocks on the heap many times
	iMaxAllocations = 10000;
	int iAllocatedMemSize = 1024; // in bytes
	for(i = 0; i < iMaxAllocations; ++i)
	{
		void * test_mem = kmalloc(iAllocatedMemSize);
		kfree(test_mem);
		test_mem = NULL;
	}

	kdbg_printmem();
}
