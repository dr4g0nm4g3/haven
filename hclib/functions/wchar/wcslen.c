/*
    Summary: wcslen.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcslen( const wchar_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcslen
   Calculates the length of s

   Returns the amount of characters in s*/

size_t wcslen( const wchar_t * s )
{
    size_t rc = 0;
    while ( s[rc] )
    {
        ++rc;
    }
    return rc;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>


#endif
