/* $Id: ldiv.c 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* ldiv( long int, long int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

ldiv_t ldiv( long int numer, long int denom )
{
    ldiv_t rc;
    rc.quot = numer / denom;
    rc.rem  = numer % denom;
    /* TODO: pre-C99 compilers might require modulus corrections */
    return rc;
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#ifndef _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

int main()
{
    ldiv_t div;
    BEGIN_TESTS;
    div = ldiv( 5, 2 );
    TESTCASE( div.quot == 2 && div.rem == 1 );
    div = ldiv( -5, 2 );
    TESTCASE( div.quot == -2 && div.rem == -1 );
    div = ldiv( 5, -2 );
    TESTCASE( div.quot == -2 && div.rem == 1 );
    TESTCASE( sizeof( div.quot ) == _HCLIB_LONG_BYTES );
    TESTCASE( sizeof( div.rem )  == _HCLIB_LONG_BYTES );
    return TEST_RESULTS;
}

#endif
