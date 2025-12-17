/*
    Summary: fwrite.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* fwrite( const void *, size_t, size_t, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <_HCLIB_glue.h>

#ifndef REGTEST

size_t fwrite( const void * _HCLIB_restrict ptr, size_t size, size_t nmemb, struct _HCLIB_file_t * _HCLIB_restrict stream )
{
    return _HCLIB_write( stream->handle, ptr, size * nmemb );
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

int main( void )
{
    FILE * fh;
    TESTCASE( ( fh = fopen( "testfile", "w" ) ) != NULL );
    TESTCASE( fwrite( "SUCCESS testing fwrite()\n", 1, 25, fh ) == 25 );
    TESTCASE( fclose( fh ) == 0 );
    /* TODO: Add readback test. */
    TESTCASE( remove( "testfile" ) == 0 );
    return TEST_RESULTS;
}

#endif
