#ifndef HKTHREAD_H_
#define HKTHREAD_H_

#include <system.h>
#include <kernel.h>

#define MAX_HKTHREADS 100	// arbitrary #

typedef struct hkthread_s
{
	uint32_t id;			// unique thread id
	uint32_t esp, ebp;		// stack and base pointers
	uint32_t eip;			// instruction pointer
	uint32_t eflags;		// eflags register
} hkthread;

// function prototypes

void init_hkthread_env();

void free_hkthread_env();

// get the id of the currently running thread
unsigned long get_hkthread_id();

// create a new thread
unsigned long create_hkthread(unsigned long func_ptr, void * data);

/* get next thread in the queue */
hkthread * hkthread_next();

// switch thread execution
int hkthread_context_switch(unsigned long id);

// delete thread and reclaim any memory in use by it
int reclaim_hkthread(unsigned long id);

#endif /*HKTHREAD_H_*/
