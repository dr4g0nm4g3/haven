/* $Id: _HCLIB_aux.h 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* Auxiliary PDCLib code <_HCLIB_aux.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* You should not have to edit anything in this file; if you DO have to, it   */
/* would be considered a bug / missing feature: notify the author(s).         */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Standard Version                                                           */
/* -------------------------------------------------------------------------- */

/* Many a compiler gets this wrong, so you might have to hardcode it instead. */

#if __STDC__ != 1
#error Compiler does not define _ _STDC_ _ to 1 (not standard-compliant)!
#endif

#ifndef __STDC_VERSION__
#define _HCLIB_C_VERSION 90
#define _HCLIB_restrict
#define _HCLIB_inline
#elif __STDC_VERSION__ == 199409L
#define _HCLIB_C_VERSION 95
#define _HCLIB_restrict
#define _HCLIB_inline
#elif __STDC_VERSION__ == 199901L
#define _HCLIB_C_VERSION 99
#define _HCLIB_restrict restrict
#define _HCLIB_inline inline
#else
#error Unsupported _ _STDC_VERSION_ _ (__STDC_VERSION__) (supported: ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999).
#endif

#ifndef __STDC_HOSTED__
#error Compiler does not define _ _STDC_HOSTED_ _ (not standard-compliant)!
#elif __STDC_HOSTED__ == 0
#define _HCLIB_HOSTED 0
#elif __STDC_HOSTED__ == 1
#define _HCLIB_HOSTED 1
#else
#error Compiler does not define _ _STDC_HOSTED_ _ to 0 or 1 (not standard-compliant)!
#endif

#if _HCLIB_C_VERSION != 99
#error PDCLib might not be fully conforming to either C89 or C95 prior to v2.x.
#endif

/* -------------------------------------------------------------------------- */
/* Helper macros:                                                             */
/* _HCLIB_cc( x, y ) concatenates two preprocessor tokens without extending  */
/* _HCLIB_concat( x, y ) concatenates two preprocessor tokens with extending */
/* -------------------------------------------------------------------------- */

#define _HCLIB_cc( x, y )     x ## y
#define _HCLIB_concat( x, y ) _HCLIB_cc( x, y )

#define _HCLIB_symbol2value( x ) #x
#define _HCLIB_symbol2string( x ) _HCLIB_symbol2value( x )
#define _HCLIB_symbol2identity( x ) x
