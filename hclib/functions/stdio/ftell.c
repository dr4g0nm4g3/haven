/*
    Summary: ftell.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* ftell( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

long int ftell( struct _HCLIB_file_t * stream )
{
    /* TODO: Implement. */
    return 0;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
