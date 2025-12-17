/*
 * errno.h - defines common error return values
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#ifndef _HCLIB_ERRNO_H
#define _HCLIB_ERRNO_H _HCLIB_ERRNO_H

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

//TODO: EDOM and ERANGE macros may need to be changed later
// represents a domain error returned by some math functions
#define EDOM 0x000001

// represents a range error returned by some math functions
#define ERANGE 0x000002

// if an error occurs, errno is assigned the value of that error
int errno = 0;

#endif // _HCLIB_ERRNO_H
