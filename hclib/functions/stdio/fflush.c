/*
    Summary: fflush.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* fflush( FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST
#include <_HCLIB_glue.h>

extern struct _HCLIB_file_t * _HCLIB_filelist;

int fflush( struct _HCLIB_file_t * stream )
{
    if ( stream == NULL )
    {
        stream = _HCLIB_filelist;
        /* TODO: Check what happens when fflush( NULL ) encounters write errors, in other libs */
        int rc = 0;
        while ( stream != NULL )
        {
            if ( stream->bufidx > stream->bufend )
            {
                rc |= _HCLIB_fflush( stream );
            }
            stream = stream->next;
        }
        return rc;
    }
    else
    {
        return _HCLIB_fflush( stream );
    }
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

