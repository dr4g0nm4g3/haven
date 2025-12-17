/*
    Summary: wcsncmp.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcsncat( wchar_t *, const wchar_t *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcsncmp
   Compares at most n characters of s1 to n characters of s2

   Returns the result of the comparison */

#include <wchar.h>

int wcsncmp(const wchar_t * s1, const wchar_t * s2, size_t n)
{
    while ( *s1 && n && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
        --n;
    }
    if ( ( n == 0 ) )
    {
        return 0;
    }
    else
    {
        return ( *s1 - *s2 );
    }
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
