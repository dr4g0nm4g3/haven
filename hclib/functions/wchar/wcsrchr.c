/*
    Summary: wcsrchr.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcsrchr( const wchar_t *, wchar_t c )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcsrchr
   Finds the last character in s that matches c

   Returns a pointer to the last character in s1 that matches c

   Returns NULL if c does not occur in s */

wchar_t * wcsrchr( const wchar_t * s, wchar_t c )
{
    size_t i = 0;
    while ( s[i++] );
    do
    {
        if ( s[--i] == c )
        {
            return (wchar_t *) s + i;
        }
    } while ( i );
    return NULL;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>


#endif
