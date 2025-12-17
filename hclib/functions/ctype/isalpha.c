/*
 * int isalpha(int ch) - tests for a letter from a-z, A-Z
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int isalpha(int ch)
{	// test A-Z
    if(ch <= 90 && ch >= 65)
         return true;
    // test a-z
    else if(ch <= 122 && ch >= 97)
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
    TESTCASE( isalpha('A') == true );
    TESTCASE( isalpha('Z') == true );
    TESTCASE( isalpha('a') == true );
    TESTCASE( isalpha('z') == true );
    TESTCASE( isalpha(0) == true );
    TESTCASE( isalpha(9328755) == true );
    TESTCASE( isalpha('.') == false );
    TESTCASE( isalpha(']') == false );
    TESTCASE( isalpha(c) == true );
    TESTCASE( isalpha(d) == false);
    return TEST_RESULTS;
}

#endif // TEST
