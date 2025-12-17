/*
    Summary: Xdigits.c
    *definition of hexadecimal digits*

    Author:
        Martin 'Solar' Baute

    License:
        Public Domain
*/

/* _HCLIB_Xdigits

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

char _HCLIB_Xdigits[] = "0123456789ABCDEF";

#ifdef TEST
#include <_HCLIB_test.h>

#include <string.h>

int main( void )
{
    TESTCASE( strcmp( _HCLIB_Xdigits, "0123456789ABCDEF" ) == 0 );
    return TEST_RESULTS;
}

#endif
