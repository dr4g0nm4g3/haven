/*
    Summary: wmemcmp.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wmemcmp( const char *, const char *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wmemcmp
   Compares at most n bytes of s1 to s2

   Returns positive if the value of s1 is larger than s2

   Returns negative if the value of s1 is smaller than s2

   Returns zero if s1 equals s2 */

int wmemcmp( const wchar_t * s1, const wchar_t * s2, size_t n )
{
    while (n && ( *s1 == *s2 ) )
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
