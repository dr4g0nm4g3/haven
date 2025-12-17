/*
    Summary: filemode.c
    Contains functions to decode the file open mode

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* _HCLIB_filemode( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include <stddef.h>

/* Helper function that parses the C-style mode string passed to fopen() into
   the PDCLib flags FREAD, FWRITE, FAPPEND, FRW (read-write) and FBIN (binary
   mode).
*/
unsigned int _HCLIB_filemode( char const * const mode )
{
    int rc = 0;
    size_t i;
    switch ( mode[0] )
    {
        case 'r':
            rc |= _HCLIB_FREAD;
            break;
        case 'w':
            rc |= _HCLIB_FWRITE;
            break;
        case 'a':
            rc |= _HCLIB_FAPPEND;
            break;
        default:
            /* Other than read, write, or append - invalid */
            return 0;
    }
    for ( i = 1; i < 4; ++i )
    {
        switch ( mode[i] )
        {
            case '+':
                if ( rc & _HCLIB_FRW ) return 0; /* Duplicates are invalid */
                rc |= _HCLIB_FRW;
                break;
            case 'b':
                if ( rc & _HCLIB_FBIN ) return 0; /* Duplicates are invalid */
                rc |= _HCLIB_FBIN;
                break;
            case '\0':
                /* End of mode */
                return rc;
            default:
                /* Other than read/write or binary - invalid. */
                return 0;
        }
    }
    /* Longer than three chars - invalid. */
    return 0;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

int main( void )
{
#ifndef REGTEST
    TESTCASE( _HCLIB_filemode( "r" ) == _HCLIB_FREAD );
    TESTCASE( _HCLIB_filemode( "w" ) == _HCLIB_FWRITE );
    TESTCASE( _HCLIB_filemode( "a" ) == _HCLIB_FAPPEND );
    TESTCASE( _HCLIB_filemode( "r+" ) == ( _HCLIB_FREAD | _HCLIB_FRW ) );
    TESTCASE( _HCLIB_filemode( "w+" ) == ( _HCLIB_FWRITE | _HCLIB_FRW ) );
    TESTCASE( _HCLIB_filemode( "a+" ) == ( _HCLIB_FAPPEND | _HCLIB_FRW ) );
    TESTCASE( _HCLIB_filemode( "rb" ) == ( _HCLIB_FREAD | _HCLIB_FBIN ) );
    TESTCASE( _HCLIB_filemode( "wb" ) == ( _HCLIB_FWRITE | _HCLIB_FBIN ) );
    TESTCASE( _HCLIB_filemode( "ab" ) == ( _HCLIB_FAPPEND | _HCLIB_FBIN ) );
    TESTCASE( _HCLIB_filemode( "r+b" ) == ( _HCLIB_FREAD | _HCLIB_FRW | _HCLIB_FBIN ) );
    TESTCASE( _HCLIB_filemode( "w+b" ) == ( _HCLIB_FWRITE | _HCLIB_FRW | _HCLIB_FBIN ) );
    TESTCASE( _HCLIB_filemode( "a+b" ) == ( _HCLIB_FAPPEND | _HCLIB_FRW | _HCLIB_FBIN ) );
    TESTCASE( _HCLIB_filemode( "rb+" ) == ( _HCLIB_FREAD | _HCLIB_FRW | _HCLIB_FBIN ) );
    TESTCASE( _HCLIB_filemode( "wb+" ) == ( _HCLIB_FWRITE | _HCLIB_FRW | _HCLIB_FBIN ) );
    TESTCASE( _HCLIB_filemode( "ab+" ) == ( _HCLIB_FAPPEND | _HCLIB_FRW | _HCLIB_FBIN ) );
#else
    puts( " NOTEST fopen() test driver is PDCLib-specific." );
#endif
    return TEST_RESULTS;
}

#endif
