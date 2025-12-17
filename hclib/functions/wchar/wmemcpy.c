/*
    Summary: wmemcpy.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wmemcpy( wchar_t *, const wchar_t *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wmemcpy
   Copies the n wide characters from s2 to s1

   Returns the value of s1 */

wchar_t *wmemcpy(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, size_t n)
{
    wchar_t * rc = s1;
    while (n > 0)
    {
        *s1++ = *s2++;
        n--;
    }
    return rc;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
