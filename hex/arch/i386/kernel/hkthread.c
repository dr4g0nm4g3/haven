/**
 * hkthread.c - implementation of kernel threads
 *
 *@author Jeff DiClemente
 *@date 11.16.2008
 */

#include <hkthread.h>
#include <ordered_array.h>
#include <kmm.h>

// currently running thread
volatile hkthread * current_thread;

/* current thread's index in the thread queue */
volatile unsigned long current_thread_idx;

// queue of ready threads
ordered_array_t * thread_queue;

// id of next thread created
static unsigned long next_id = 1;

void init_hkthread_env()
{
	*thread_queue = create_ordered_array(MAX_HKTHREADS, (fn_lessthan)0, (fn_destroy)0);
	current_thread = 0;
	current_thread_idx = 0;
}

void free_hkthread_env()
{
	destroy_ordered_array(thread_queue);
	next_id = 1;
	current_thread = 0;
	current_thread_idx = 0;
}

unsigned long get_hkthread_id()
{
	if(current_thread)
		return current_thread->id;
	else
		return 0;
}

unsigned long create_hkthread(unsigned long func_ptr, void * data)
{
	hkthread * thread = (hkthread *)kmalloc(sizeof(hkthread));
	thread->id = next_id++;
	thread->eip = func_ptr;
	thread->esp = 0;
	thread->ebp = 0;
	thread->eflags = 0;

	// add to the end of the queue
	insert_ordered_array(thread_queue, thread);

	return thread->id;
}

hkthread * hkthread_next()
{
	if(thread_queue)
	{
		hkthread * thread = (hkthread *)lookup_ordered_array(thread_queue, ++current_thread_idx);
		if(thread == 0)
		{	// go to the front of the queue
			current_thread_idx = 0;
			return (hkthread *)lookup_ordered_array(thread_queue, current_thread_idx);
		}
		else
		{
			return thread;
		}
	}
	return (hkthread *)0;
}

int hkthread_context_switch(unsigned long id)
{
	if(thread_queue == 0)
		return 0;

	unsigned int i = 0;
	for(; i < thread_queue->size; ++i)
	{
		hkthread * thread = (hkthread *)lookup_ordered_array(thread_queue, i);
		if(thread)
		{
			if(thread->id == id)
			{
				// TODO: switch to this thread
				/* disable interrupts */
				__asm__ __volatile__ ("cli");

				current_thread = thread;

				/* enable interrupts */
				__asm__ __volatile__ ("sti");
			}
		}
	}
	return 0;
}
