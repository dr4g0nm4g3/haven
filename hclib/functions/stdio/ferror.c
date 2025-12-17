/*
    Summary: ferror.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* ferror( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int ferror( struct _HCLIB_file_t * stream )
{
    return stream->status & _HCLIB_ERRORFLAG;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

int main( void )
{
    /* Testing covered by clearerr(). */
    return TEST_RESULTS;
}

#endif
