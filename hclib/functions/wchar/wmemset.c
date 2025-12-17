/*
    Summary: wmemset.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wmemset( wchar_t *, wchar_t, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wmemset
   Fills s with n times the value c

   Returns the value of s */

wchar_t * wmemset( wchar_t * s, wchar_t c, size_t n )
{
    wchar_t * p = s;
    while ( n-- )
    {
        *p++ = (unsigned char) c;
    }
    return s;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>


#endif
