/*
    Summary: wmemmove.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wmemmove( wchar_t *, const wchar_t *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wmemmove
   Copies n wide characters from s2 to s1, where s2 and s1 can overlap

   Returns the value of s1 */

wchar_t * wmemmove( wchar_t * s1, const wchar_t * s2, size_t n )
{
    wchar_t * dest = (wchar_t *) s1;
    const wchar_t * src = (const wchar_t *) s2;
    if ( dest <= src )
    {
        while ( n-- )
        {
            *dest++ = *src++;
        }
    }
    else
    {
        src += n;
        dest += n;
        while ( n-- )
        {
            *--dest = *--src;
        }
    }
    return s1;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
