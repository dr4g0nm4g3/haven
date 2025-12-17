/*
 * int isalnum(int ch) - tests for a letter or digit
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int isalnum(int ch)
{   
	return (isalpha(ch) || isdigit(ch))?true:false;
}

#endif // REGTEST

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    char c = 'G';
    char d = '-';
    BEGIN_TESTS;
    TESTCASE( isalnum('A') == true );
    TESTCASE( isalnum('Z') == true );
    TESTCASE( isalnum('a') == true );
    TESTCASE( isalnum('z') == true );
    TESTCASE( isalnum(0) == true );
    TESTCASE( isalnum(9328755) == true );
    TESTCASE( isalnum('.') == false );
    TESTCASE( isalnum(']') == false );
    TESTCASE( isalnum(c) == true );
    TESTCASE( isalnum(d) == false);
    return TEST_RESULTS;
}

#endif // TEST
