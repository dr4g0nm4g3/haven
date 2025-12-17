/*
    Summary: wmemchr.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wmemchr( const wchar_t *, wchar_t, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wmemchr
   Finds the first occurance of the character c in s, where n is the maximum amount of bytes to compare

   Returns a pointer to the location in the buffer where c is found

   Returns NULL if c could not be found */

wchar_t * wmemchr( const wchar_t * s, wchar_t c, size_t n )
{
    while ( n-- )
    {
        if ( *s == c )
        {
            return (wchar_t *) s;
        }
        ++s;
    }
    return NULL;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
