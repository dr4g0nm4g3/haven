/*
    Summary: fgets.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* fgets( char *, int, FILE * );

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

char * fgets( char * _HCLIB_restrict s, int n, struct _HCLIB_file_t * _HCLIB_restrict stream )
{
    /* TODO: Implement. */
    return NULL;
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
