/*
    Summary: sscanf.c
    *The libc implementation*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* sscanf( const char *, const char *, ... )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <stdarg.h>

#ifndef REGTEST

int sscanf( const char * _HCLIB_restrict s, const char * _HCLIB_restrict format, ... )
{
    va_list ap;
    va_start( ap, format );
    return vsscanf( s, format, ap );
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
