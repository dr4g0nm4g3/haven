/* $Id: assert.h 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* 7.2 Diagnostics <assert.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _HCLIB_AUX_H
#define _HCLIB_AUX_H _HCLIB_AUX_H
#include <_HCLIB_aux.h>
#endif

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

#ifndef _HCLIB_ASSERT_H
#define _HCLIB_ASSERT_H _HCLIB_ASSERT_H
#if _HCLIB_C_VERSION == 99
void _HCLIB_assert( char const * const, char const * const, char const * const );
#else
void _HCLIB_assert( char const * const );
#endif
#endif

/* If NDEBUG is set, assert() is a null operation. */
#undef assert

#ifdef NDEBUG
#define assert( ignore ) ( (void) 0 )
#else
#if _HCLIB_C_VERSION == 99
#define assert( expression ) ( ( expression ) ? (void) 0 \
        : _HCLIB_assert( "Assertion failed: " #expression \
                          ", function ", __func__, \
			  ", file " __FILE__ \
			  ", line " _HCLIB_symbol2string( __LINE__ ) \
			  "." _HCLIB_endl ) )
#else
#define assert( expression ) ( ( expression ) ? (void) 0 \
	: _HCLIB_assert( "Assertion failed: " #expression \
	                  ", file " __FILE__ \
	                  ", line " _HCLIB_symbol2string( __LINE__ ) \
	                  "." _HCLIB_endl ) )
#endif
#endif

