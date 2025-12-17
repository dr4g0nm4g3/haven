/*
 * syscall.c
 *
 *  Created on: Jun 8, 2014
 *      Author: dragon
 */

#include <syscall.h>
#include <console.h>
#include <kdbg.h>

// ISR implemented in syscalls.s
extern void _isr80();

/*
 * Right now, these are defined in the kernel, but
 * ultimately these will be function definitions
 * in a user library and called from user mode
 */
DEFN_SYSCALL0(TestSyscallParam0, 0);
DEFN_SYSCALL1(TestSyscallParam1, 1, const char *);
DEFN_SYSCALL2(TestSyscallParam2, 2, const char *, const char *);

/*
 * kernel implementations of system calls
 * These will not be accessible to user mode directly.
 * They will only be executed via the system calls exposed
 * in a user mode library.
 */
int hk_TestSyscallParam0()
{
	kprintf("In hk_TestSyscallParam0\n");
	return -1;
}

int hk_TestSyscallParam1(const char * p1)
{
	kprintf("In hk_TestSyscallParam1 (%s)\n", p1);
	return -1;
}

int hk_TestSyscallParam2(const char * p1, const char * p2)
{
	kprintf("In hk_TestSyscallParam2 (%s, %s)\n", p1, p2);
	return -1;
}
/*
 * end - kernel implementations of system calls
 */

/*
 * Test; hard code the function pointers to
 * kernel system calls.
 */
static void *syscalls[3] = { &hk_TestSyscallParam0, &hk_TestSyscallParam1, &hk_TestSyscallParam2 };

void syscall_initialize(void)
{
	// setup syscall ISR. This is how user mode code calls
	//	into kernel functions.
	// 128d == 0x80
	set_idt_gate(128, (unsigned long)&_isr80, 0x08, 0xEE);
}

void syscall_handler(isr_context_t * ctx)
{
	kprintf("Entering syscall handler for interrupt %d\n", ctx->int_no);
	if(ctx->eax >= 0 && ctx->eax < 3)
	{
		kdbg_log("Calling system call number %d\n", ctx->eax);

		// We don't know how many parameters the function wants, so we just
		// push them all onto the stack in the correct order. The function will
		// use all the parameters it wants, and we can pop them all back off afterwards.
		int ret = -1;
		asm volatile (" \
				push %1; \
				push %2; \
				push %3; \
				push %4; \
				push %5; \
				call *%6; \
				pop %%ebx; \
				pop %%ebx; \
				pop %%ebx; \
				pop %%ebx; \
				pop %%ebx; \
				" : "=a" (ret) : "r" (ctx->edi), "r" (ctx->esi), "r" (ctx->edx), "r" (ctx->ecx), "r" (ctx->ebx), "r" (syscalls[ctx->eax]));
		ctx->eax = ret;
	}
	else
	{
		kdbg_log("Error. Unknown system call (number %d)\n", ctx->eax);
	}
}
