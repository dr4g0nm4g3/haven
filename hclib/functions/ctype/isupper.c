/*
 * int isupper(int ch) - tests whether the character is an uppercase letter (A-Z)
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int isupper(int ch)
{	// test A-Z
    if(ch <= 90 && ch >= 65)
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
    TESTCASE( isupper('A') == true );
    TESTCASE( isupper('Z') == true );
    TESTCASE( isupper('a') == false );
    TESTCASE( isupper('z') == false );
    TESTCASE( isupper(0) == false );
    TESTCASE( isupper('9') == false );
    TESTCASE( isupper('11') == false );
    TESTCASE( isupper(9328755) == false );
    TESTCASE( isupper('.') == false );
    TESTCASE( isupper(']') == false );
    TESTCASE( isupper(c) == true );
    TESTCASE( isupper(d) == false);
    return TEST_RESULTS;
}

#endif // TEST
