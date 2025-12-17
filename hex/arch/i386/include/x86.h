/*
 * x86.h
 * common x86 assembler instructions
 *
 *  Created on: Nov 8, 2009
 *      Author: dragon
 */

#ifndef X86_H_
#define X86_H_

// get current instruction pointer
extern unsigned long _read_eip();

static inline unsigned long read_esp()
{
	unsigned long esp;
	__asm__ __volatile__("mov %%esp, %0" : "=r"(esp));
	return esp;
}

static inline unsigned long read_ebp()
{
	unsigned long ebp;
	__asm__ __volatile__("mov %%ebp, %0" : "=r"(ebp));
	return ebp;
}

static inline unsigned long read_cr3()
{
	unsigned long cr3;
	__asm__ __volatile__("mov %%cr3, %0" : "=r"(cr3));
	return cr3;
}


#endif /* X86_H_ */
