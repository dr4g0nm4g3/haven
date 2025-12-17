/*
    Summary: wcspbrk.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcspbrk( const wchar_t *, const wchar_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcspbrk
   Finds the first character in s1 that occurs in s2

   Returns a pointer to a character in s1 that occurs in s2

   Returns NULL if s1 and s2 do not share any characters */

wchar_t * wcspbrk( const wchar_t * s1, const wchar_t * s2 )
{
    const wchar_t * p1 = s1;
    const wchar_t * p2;
    while ( *p1 )
    {
        p2 = s2;
        while ( *p2 )
        {
            if ( *p1 == *p2++ )
            {
                return (wchar_t *) p1;
            }
        }
        ++p1;
    }
    return NULL;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>


#endif
