/* $Id: limits.h 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* 7.10 Sizes of integer types <limits.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _HCLIB_LIMITS_H
#define _HCLIB_LIMITS_H _HCLIB_LIMITS_H

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

/* TODO: Defined to 1 as multibyte characters are not supported yet. */
#define MB_LEN_MAX 1

#define LLONG_MIN  _HCLIB_LLONG_MIN
#define LLONG_MAX  _HCLIB_LLONG_MAX
#define ULLONG_MAX _HCLIB_ULLONG_MAX

#define CHAR_BIT   _HCLIB_CHAR_BIT
#define CHAR_MAX   _HCLIB_CHAR_MAX
#define CHAR_MIN   _HCLIB_CHAR_MIN
#define SCHAR_MAX  _HCLIB_SCHAR_MAX
#define SCHAR_MIN  _HCLIB_SCHAR_MIN
#define UCHAR_MAX  _HCLIB_UCHAR_MAX
#define SHRT_MAX   _HCLIB_SHRT_MAX
#define SHRT_MIN   _HCLIB_SHRT_MIN
#define INT_MAX    _HCLIB_INT_MAX
#define INT_MIN    _HCLIB_INT_MIN
#define LONG_MAX   _HCLIB_LONG_MAX
#define LONG_MIN   _HCLIB_LONG_MIN
#define USHRT_MAX  _HCLIB_USHRT_MAX
#define UINT_MAX   _HCLIB_UINT_MAX
#define ULONG_MAX  _HCLIB_ULONG_MAX

#endif

