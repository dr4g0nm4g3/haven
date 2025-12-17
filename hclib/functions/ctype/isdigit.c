/*
 * int isdigit(int ch) - tests for a digit from 0-9
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int isdigit(int ch)
{	// test 0-9
    if(ch <= 57 && ch >= 48)
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
    TESTCASE( isdigit('A') == false );
    TESTCASE( isdigit('Z') == false );
    TESTCASE( isdigit('a') == false );
    TESTCASE( isdigit('z') == false );
    TESTCASE( isdigit(0) == true );
    TESTCASE( isdigit('9') == true );
    TESTCASE( isdigit('11') == true );
    TESTCASE( isdigit(9328755) == true );
    TESTCASE( isdigit('.') == false );
    TESTCASE( isdigit(']') == false );
    TESTCASE( isdigit(c) == false );
    TESTCASE( isdigit(d) == false);
    return TEST_RESULTS;
}

#endif // TEST
