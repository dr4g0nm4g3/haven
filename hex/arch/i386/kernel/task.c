/*
 * task.c
 *
 *  Created on: Jun 8, 2014
 *      Author: dragon
 */

/* reference:
 * http://www.jamesmolloy.co.uk/tutorial_html/10.-User%20Mode.html
 *
 * Switch from kernel mode to user mode
 *
 * This function sets all the segment registers to user mode
 * data selectors, saves the stack, modifies the EFLAGS register
 * so that interrupts are enabled after the iret and then
 * returns into user code.
 *
 * When this function returns, code will be executing in
 * user mode.
 */
#include <syscall.h>
#include <system.h>

/* test function that will execute in ring3 */
void userland_func()
{
	_bochs_magic_break();
	hkTestSyscallParam0();

	// hlt is a privileged instruction.
	// it should cause a general protection fault.
	__asm__ __volatile__ ("hlt");
}

void switch_to_user_mode()
{
	// Set up a stack structure for switching to user mode.
	__asm__ __volatile__("  \
			cli; \
			mov $0x23, %%ax; \
			mov %%ax, %%ds; \
			mov %%ax, %%es; \
			mov %%ax, %%fs; \
			mov %%ax, %%gs; \
			\
			mov %%esp, %%eax; \
			push $0x23; \
			push %%eax; \
			pushf; \
			pop %%eax; \
			or $0x200, %%eax; \
			push %%eax; \
			push $0x1b; \
			push %0; \
			iret; \
			" : : "d" (&userland_func));
}
