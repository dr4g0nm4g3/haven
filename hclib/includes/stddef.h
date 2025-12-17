/* $Id: stddef.h 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* 7.17 Common definitions <stddef.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _HCLIB_STDDEF_H
#define _HCLIB_STDDEF_H _HCLIB_STDDEF_H

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

typedef _HCLIB_ptrdiff_t ptrdiff_t;

#ifndef _HCLIB_SIZE_T_DEFINED
#define _HCLIB_SIZE_T_DEFINED _HCLIB_SIZE_T_DEFINED
typedef _HCLIB_size_t size_t;
#endif

typedef _HCLIB_wchar_t   wchar_t;

#ifndef _HCLIB_NULL_DEFINED
#define _HCLIB_NULL_DEFINED _HCLIB_NULL_DEFINED
#define NULL _HCLIB_NULL
#endif

#define offsetof( type, member ) _HCLIB_offsetof( type, member )

#endif

