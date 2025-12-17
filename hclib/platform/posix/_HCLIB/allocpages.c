/* $Id: allocpages.c 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* _HCLIB_allocpages( int const )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _HCLIB_allocpages() (declared in
   _HCLIB_config.h), TODO: fit to use with HAVEN kernel
*/

#include <stdint.h>
#include <stddef.h>

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

int brk( void * );
void * sbrk( intptr_t );

static void * membreak = NULL;

void * _HCLIB_allocpages( int const n )
{
    if ( membreak == NULL )
    {
        /* first call, make sure end-of-heap is page-aligned */
        intptr_t unaligned = 0;
        membreak = sbrk( 0 );
        unaligned = _HCLIB_PAGESIZE - (intptr_t)membreak % _HCLIB_PAGESIZE;
        if ( unaligned < _HCLIB_PAGESIZE )
        {
            /* end-of-heap not page-aligned - adjust */
            if ( sbrk( unaligned ) != membreak )
            {
                /* error */
                return NULL;
            }
            membreak = (char *)membreak + unaligned;
        }
    }
    /* increasing or decreasing heap - standard operation */
    void * oldbreak = membreak;
    membreak = (void *)( (char *)membreak + ( n * _HCLIB_PAGESIZE ) );
    if ( brk( membreak ) == 0 )
    {
        /* successful */
        return oldbreak;
    }
    else
    {
        /* out of memory */
        membreak = oldbreak;
        return NULL;
    }
}

#ifdef TEST
#include <_HCLIB_test.h>

int puts( const char * );

int main()
{
    BEGIN_TESTS;
#ifndef REGTEST
    {
    void * startbreak = sbrk( 0 );
    TESTCASE( _HCLIB_allocpages( 0 ) );
    TESTCASE( ( sbrk( 0 ) - startbreak ) <= _HCLIB_PAGESIZE );
    startbreak = sbrk( 0 );
    TESTCASE( _HCLIB_allocpages( 1 ) );
    TESTCASE( sbrk( 0 ) == startbreak + ( 1 * _HCLIB_PAGESIZE ) );
    TESTCASE( _HCLIB_allocpages( 5 ) );
    TESTCASE( sbrk( 0 ) == startbreak + ( 6 * _HCLIB_PAGESIZE ) );
    TESTCASE( _HCLIB_allocpages( -3 ) );
    TESTCASE( sbrk( 0 ) == startbreak + ( 3 * _HCLIB_PAGESIZE ) );
    }
#endif
    return TEST_RESULTS;
}

#endif

