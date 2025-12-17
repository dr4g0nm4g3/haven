/*
 * setjmp.h - low level calls and returns from functions
 * 
 * date: 08/18/2007
 * author: Jeff DiClemente
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

// TODO: implementation

#ifndef _HCLIB_SETJMP_H
#define _HCLIB_SETJMP_H _HCLIB_SETJMP_H

#ifndef _HCLIB_AUX_H
#define _HCLIB_AUX_H _HCLIB_AUX_H
#include <_HCLIB_aux.h>
#endif

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

/* used to hold environment information for short and long jumps */
typedef jmp_buf void *;

/* saves the environment information into env. a non-zero value is returned if the point in the source code
 * was reached nby a long jump. otherwise zero is returned indicating the jump has been saved 
 */ 
int setjmp(jmp_buf env);

/* causes the environment to be restored from a setjmp. Execution goes to the setjmp function as if setjmp
 * had returned the value of the variable value. Value cannot be zero, if zero is passed, then 1 is replaced.
 * If the function where setjmp was called has terminated, results are undefined
 */
void longjump(jmp_buf env, int value);

#endif /* _HCLIB_SETJMP_H */
