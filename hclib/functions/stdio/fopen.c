/*
    Summary: fopen.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* fopen( const char *, const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef REGTEST
#include <_HCLIB_glue.h>

/* FIXME: This approach is a possible attack vector. */
FILE * _HCLIB_filelist = NULL;

FILE * fopen( const char * _HCLIB_restrict filename, const char * _HCLIB_restrict mode )
{
    FILE * rc;
    if ( mode == NULL || filename == NULL || filename[0] == '\0' )
    {
        /* Mode or filename invalid */
        return NULL;
    }
    if ( ( rc = calloc( 1, sizeof( struct _HCLIB_file_t ) ) ) == NULL )
    {
        /* no memory for another FILE */
        return NULL;
    }
    if ( ( rc->status = _HCLIB_filemode( mode ) ) == 0 ) goto fail; /* invalid mode */
    rc->handle = _HCLIB_open( filename, rc->status );
    if ( rc->handle == _HCLIB_NOHANDLE ) goto fail; /* OS open() failed */
    /* Adding to list of open files */
    rc->next = _HCLIB_filelist;
    _HCLIB_filelist = rc;
    /* Setting buffer, and mark as internal. TODO: Check for unbuffered */
    if ( ( rc->buffer = malloc( BUFSIZE ) ) == NULL ) goto fail;
    rc->bufsize = BUFSIZE;
    rc->bufidx = 0;
    /* Setting buffer to _IOLBF because "when opened, a stream is fully
       buffered if and only if it can be determined not to refer to an
       interactive device."
    */
    rc->status |= ( _HCLIB_LIBBUFFER | _HCLIB_VIRGINSTR /* | _IOLBF */ ); /* FIXME: Uncommenting the _IOLBF here breaks output. */
    /* TODO: Setting mbstate */
    return rc;
fail:
    free( rc );
    return NULL;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

int main( void )
{
    /* Some of the tests are not executed for regression tests, as the libc on
       my system is at once less forgiving (segfaults on mode NULL) and more
       forgiving (accepts undefined modes).
    */
#ifndef REGTEST
    TESTCASE( fopen( NULL, NULL ) == NULL );
#endif
    TESTCASE( fopen( NULL, "w" ) == NULL );
#ifndef REGTEST
    TESTCASE( fopen( "", NULL ) == NULL );
#endif
    TESTCASE( fopen( "", "w" ) == NULL );
    TESTCASE( fopen( "foo", "" ) == NULL );
#ifndef REGTEST
    TESTCASE( fopen( "testfile", "wq" ) == NULL ); /* Undefined mode */
    TESTCASE( fopen( "testfile", "wr" ) == NULL ); /* Undefined mode */
#endif
    TESTCASE( fopen( "testfile", "w" ) != NULL );
    system( "rm testfile" );
    return TEST_RESULTS;
}

#endif
