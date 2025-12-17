/*
    Summary: fread.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* fread( void *, size_t, size_t, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <_HCLIB_glue.h>

#ifndef REGTEST

size_t fread( void * _HCLIB_restrict ptr, size_t size, size_t nmemb, struct _HCLIB_file_t * _HCLIB_restrict stream )
{
    return _HCLIB_read( stream->handle, ptr, size * nmemb );
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

int main( void )
{
    /* Testing handled by fwrite(). */
    return TEST_RESULTS;
}

#endif
