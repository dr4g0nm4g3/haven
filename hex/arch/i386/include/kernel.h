#ifndef KERNEL_H_
#define KERNEL_H_

/*  contains data structures and function prototypes for kernel */

#include "hktypes.h"

#define HEX_VERSION_STR "0.0.2"

/* Internal error codes */
#define HEX_FAILURE 0
#define HEX_SUCCESS 1
#define HEX_OUT_OF_MEMORY 2

/* Forward declarations. */
void _main(void * mbd, unsigned long magic, unsigned long initial_stack_ptr);
void hex_init();

#endif /*KERNEL_H_*/
