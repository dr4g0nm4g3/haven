/*
    Summary: wcschr.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcschr( const wchar_t *, wchar_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcschr
   Finds the first occurance of the character c in the null-terminated string s

   Returns a pointer to the location in the string where c is found

   Returns NULL if c could not be found */

wchar_t * wcschr( const wchar_t * s, wchar_t c )
{
    do
    {
        if ( *s == c )
        {
            return (wchar_t *) s;
        }
    } while ( *s++ );
    return NULL;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>


#endif
