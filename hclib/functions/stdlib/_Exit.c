/* $Id: _Exit.c 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* _Exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>

#ifndef REGTEST

void _Exit( int status )
{
    /* TODO: Flush and close open streams. Remove tmpfile() files. */
    _HCLIB_Exit( status );
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    /* TODO: Add testdrivers after flush / close / tmpfile is implemented. */
    return TEST_RESULTS;
}

#endif
