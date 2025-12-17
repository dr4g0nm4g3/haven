/*
    Summary: fseek.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* fseek( FILE *, long int, int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int fseek( struct _HCLIB_file_t * stream, long int offset, int whence )
{
    if ( stream->status & _HCLIB_WROTELAST )
    {
        fflush( stream );
    }
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
