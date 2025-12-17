/*
    Summary: wcscspn.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcscspn( const wchar_t *, const wchar_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcscspn
  Tests characters in s1 for an occurance in s2 until a match is found

   Returns the amount of characters from the beginning of s1 that do NOT occur in s2 */

size_t wcscspn( const wchar_t * s1, const wchar_t * s2 )
{
    size_t len = 0;
    const wchar_t * p;
    while ( s1[len] )
    {
        p = s2;
        while ( *p )
        {
            if ( s1[len] == *p++ )
            {
                return len;
            }
        }
        ++len;
    }
    return len;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
