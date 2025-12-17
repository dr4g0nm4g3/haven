/**
 * tss.c - functions for initializing and modifying a TSS
 * 
 *@author Jeff DiClemente
 *@date 11.15.2008
 */

#include <common.h>
#include <system.h>
#include <kernel.h>
#include <kdbg.h>

 extern unsigned long initial_esp;

void load_task_register(unsigned int seg_selector)
{
	__asm__ __volatile__ ("ltr %%ax"::"a"(seg_selector));
}

void init_tss(tss_t * sys_tss)
{
	memset(sys_tss, 0, sizeof(tss_t));

	/*
		When the processor performs a call to the exception- or interrupt-handler procedure:
 		If the handler procedure is going to be executed at a numerically lower privilege level, a stack switch occurs.
		When the stack switch occurs:
			The segment selector and stack pointer for the stack to be used by the handler are obtained from the TSS
			for the currently executing task. On this new stack, the processor pushes the stack segment selector and
			stack pointer of the interrupted procedure.

		We only have one stack at the moment, the kernel's. Use this stack when user mode code
		invokes an interrupt.
	*/
	set_ring0_stack(sys_tss, initial_esp, 0x10);

	// Here we set the cs, ss, ds, es, fs and gs entries in the TSS. These specify what
	// segments should be loaded when the processor switches to kernel mode. Therefore
	// they are just our normal kernel code/data segments - 0x08 and 0x10 respectively,
	// but with the last two bits set, making 0x0b and 0x13. The setting of these bits
	// sets the RPL (requested privilege level) to 3, meaning that this TSS can be used
	// to switch to kernel mode from ring 3.
	sys_tss->cs = 0x0b;
	sys_tss->ss = sys_tss->ds = sys_tss->es = sys_tss->fs = sys_tss->gs = 0x13;
}

void set_ring0_stack(tss_t * sys_tss, unsigned long esp, unsigned long ss)
{
	sys_tss->esp0 = esp;
	sys_tss->ss0 = ss;
}
