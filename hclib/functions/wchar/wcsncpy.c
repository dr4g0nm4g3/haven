
/*
    Summary: wcsncpy.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcsncpy( wchar_t *, const wchar_t *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcsncpy
   Copies the null terminated wide string s2 to s1.
   Copies at most n characters, if there are less, it will write zeroes.

   Returns the value of s1 */

wchar_t * wcsncpy( wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, size_t n )
{
    wchar_t * rc = s1;
    while ( ( n > 0 ) && ( *s1++ = *s2++ ) )
    {
        /* Cannot do "n--" in the conditional as size_t is unsigned and we have
        to check it again for >0 in the next loop.
        */
        --n;
    }
    while ( --n )
    {
        *s1++ = '\0';
    }
    return rc;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
