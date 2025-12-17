/* $Id: seed.c 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* _HCLIB_seed

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

unsigned long int _HCLIB_seed = 1;

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    /* no tests for raw data */
    return TEST_RESULTS;
}

#endif
