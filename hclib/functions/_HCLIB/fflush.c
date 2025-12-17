/*
    Summary: fflush.c
    the helper function for <fflush>

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* _HCLIB_fflush( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

/* Function: _HCLIB_fflush
 *
 * this function flushes the output stream.
 */
int _HCLIB_fflush( struct _HCLIB_file_t * stream )
{
    if ( fwrite( stream->buffer, stream->bufidx, 1, stream ) == stream->bufidx )
    {
        stream->bufidx = 0;
        return 0;
    }
    else
    {
        stream->status |= _HCLIB_ERRORFLAG;
        return EOF;
    }
}

#ifdef TEST
#include <_HCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif

