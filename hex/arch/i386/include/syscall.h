/*
 * syscall.h
 * functions to initialize and handle system calls
 *
 *  Created on: Jun 8, 2014
 *      Author: dragon
 */

#ifndef SYSCALL_H_
#define SYSCALL_H_

#include <idt.h>

/*
 * Helper macros to invoke system calls.
 * Ultimately, this will be in a user library.
 * For now, this is for testing purposes within
 * the kernel itself to test task/context switching.
 */
#define DECL_SYSCALL0(fn) int hk##fn();
#define DECL_SYSCALL1(fn,p1) int hk##fn(p1);
#define DECL_SYSCALL2(fn,p1,p2) int hk##fn(p1,p2);

#define DEFN_SYSCALL0(fn, num) \
int hk##fn() \
{ \
	int a; \
	__asm__ __volatile__("int $0x80" : "=a" (a) : "0" (num)); \
	return a; \
}

#define DEFN_SYSCALL1(fn, num, P1) \
int hk##fn(P1 p1) \
		{ \
	int a; \
	__asm__ __volatile__("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1)); \
	return a; \
		}

#define DEFN_SYSCALL2(fn, num, P1, P2) \
int hk##fn(P1 p1, P2 p2) \
		{ \
	int a; \
	__asm__ __volatile__("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2)); \
	return a; \
		}

DECL_SYSCALL0(TestSyscallParam0);
DECL_SYSCALL1(TestSyscallParam1, const char *);
DECL_SYSCALL2(TestSyscallParam2, const char *, const char *);

void syscall_initialize(void);

void syscall_handler(isr_context_t *);

#endif /* SYSCALL_H_ */
