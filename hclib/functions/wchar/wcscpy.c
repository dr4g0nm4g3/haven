/*
    Summary: wcscpy.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcscpy( wchar_t *, const wchar_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcscpy
   Copies the null terminated wide string s2 to s1

   Returns the value of s1 */

wchar_t *wcscpy(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2)
{
    wchar_t * rc = s1;
    while ( ( *s1++ = *s2++ ) );
    return rc;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
