/*
 * int toupper(int ch) - converts the character, assuming its a letter to uppercase
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int toupper(int ch)
{
	if(!islower(ch))
		return ch;

	return ch - 0x20;
}

#endif // REGTEST

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    char c = 'G';
    char d = '-';
    BEGIN_TESTS;
    TESTCASE( toupper('A') == 'A' );
    TESTCASE( toupper('Z') == 'Z' );
    TESTCASE( toupper('a') == 'A' );
    TESTCASE( toupper('z') == 'Z' );
    TESTCASE( toupper(0) == 0 );
    TESTCASE( toupper('9') == '9' );
    TESTCASE( toupper('11') == '11' );
    TESTCASE( toupper(9328755) == 9328755 );
    TESTCASE( toupper('.') == '.' );
    TESTCASE( toupper(']') == ']' );
    TESTCASE( toupper(c) == 'G' );
    TESTCASE( toupper(d) == '-');
    return TEST_RESULTS;
}

#endif // TEST
