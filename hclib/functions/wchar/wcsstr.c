/*
    Summary: wcsstr.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcsstr( const wchar_t *, const wchar_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcsstr
   Finds the first occurance of s1 in s2

   Returns a pointer to the location where s1 is contained in s2

   Returns NULL if s1 could not be found inside s2 */

wchar_t * wcsstr( const wchar_t * s1, const wchar_t * s2 )
{
    const wchar_t * p1 = s1;
    const wchar_t * p2;
    while ( *s1 )
    {
        p2 = s2;
        while ( *p2 && ( *p1 == *p2 ) )
        {
            ++p1;
            ++p2;
        }
        if ( ! *p2 )
        {
            return (wchar_t *) s1;
        }
        ++s1;
        p1 = s1;
    }
    return NULL;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
