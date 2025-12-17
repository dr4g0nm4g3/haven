/*
 * kmm.h
 * 	kernel memory manager
 * 	use of these functions to allocate memory on the kernel heap is preferable
 * 	to using those found in kheap.h
 *
 *  Created on: Apr 10, 2009
 *      Author: dragon
 */

#ifndef KMM_H_
#define KMM_H_

/**
 * initialize the kernel heap
 *
 */
void kmm_init();

/**
 * kernel version of malloc to be called by all kernel functions wishing to allocate memory
 *
 * @param[in] size size of memory region to allocate
 * @return a pointer to a contiguous region of memory
 */
void * kmalloc(unsigned int size);

/**
 * kernel version of free to be called by all kernel functions wishing to deallocate memory
 *
 * @param[in] p pointer to memory region to free
 */
void kfree(void * p);

/* print out list of memory blocks for debugging purposes */
void kdbg_printmem();

#endif /* KMM_H_ */
