/* $Id: free.c 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* void free( void * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

/* TODO: Primitive placeholder. Much room for improvement. */

/* structure holding first and last element of free node list */
extern struct _HCLIB_headnode_t _HCLIB_memlist;

void free( void * ptr )
{
    ptr = (void *)( (char *)ptr - sizeof( struct _HCLIB_memnode_t ) );
    ( (struct _HCLIB_memnode_t *)ptr )->next = NULL;
    if ( _HCLIB_memlist.last != NULL )
    {
        _HCLIB_memlist.last->next = ptr;
    }
    else
    {
        _HCLIB_memlist.first = ptr;
    }
    _HCLIB_memlist.last = ptr;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    /* tests covered in malloc test driver */
    return TEST_RESULTS;
}

#endif
