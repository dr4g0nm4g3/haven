/*
 * int islower(int ch) - tests whether the character is a lowercase letter (a-z)
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int islower(int ch)
{	// test a-z
    if(ch <= 122 && ch >= 97)
         return true;
    else // no match
        return false;
}

#endif // REGTEST

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    char c = 'G';
    char d = '-';
    BEGIN_TESTS;
    TESTCASE( islower('A') == false );
    TESTCASE( islower('Z') == false );
    TESTCASE( islower('a') == true );
    TESTCASE( islower('z') == true );
    TESTCASE( islower(0) == false );
    TESTCASE( islower('9') == false );
    TESTCASE( islower('11') == false );
    TESTCASE( islower(9328755) == false );
    TESTCASE( islower('.') == false );
    TESTCASE( islower(']') == false );
    TESTCASE( islower(c) == false );
    TESTCASE( islower(d) == false);
    return TEST_RESULTS;
}

#endif // TEST
