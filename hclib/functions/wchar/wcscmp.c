/*
    Summary: wcscat.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcscmp( wchar_t *, const wchar_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcscmp
   Compares s1 to s2

   Returns the result of the comparison */

#include <wchar.h>

int wcscmp(const wchar_t * s1, const wchar_t * _HCLIB_restrict s2)
{
    while ( ( *s1 ) && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
    }
    return ( *s1 - *s2 );
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
