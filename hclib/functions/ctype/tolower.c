/*
 * int tolower(int ch) - converts the character, assuming its a letter, to lowercase
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int tolower(int ch)
{
	if(!isupper(ch))
		return ch;

	return ch + 0x20;
}

#endif // REGTEST

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    char c = 'G';
    char d = '-';
    BEGIN_TESTS;
    TESTCASE( tolower('A') == 'a' );
    TESTCASE( tolower('Z') == 'z' );
    TESTCASE( tolower('a') == 'a' );
    TESTCASE( tolower('z') == 'z' );
    TESTCASE( tolower(0) == 0 );
    TESTCASE( tolower('9') == '9' );
    TESTCASE( tolower('11') == '11' );
    TESTCASE( tolower(9328755) == 9328755 );
    TESTCASE( tolower('.') == '.' );
    TESTCASE( tolower(']') == ']' );
    TESTCASE( tolower(c) == 'g' );
    TESTCASE( tolower(d) == '-');
    return TEST_RESULTS;
}

#endif // TEST
