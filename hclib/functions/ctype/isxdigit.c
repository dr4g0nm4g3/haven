/*
 * int isxdigit(int ch) - tests whether the character is a hexadecimal digit (0-9, A-F)
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int isxdigit(int ch)
{
	if(isdigit(ch))
		return true;

	// check for [A-F]
	if(ch >= 65 && ch <= 70)
		return true;

	// check for [a-f]
	if(ch >= 97 && ch <= 102)
		return true;

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
    TESTCASE( isxdigit('A') == true );
    TESTCASE( isxdigit(0x0) == true );
    TESTCASE( isxdigit(0xD) == true );
    TESTCASE( isxdigit('F') == true );
    TESTCASE( isxdigit('z') == false );
    TESTCASE( isxdigit(0) == true );
    TESTCASE( isxdigit('9') == true );
    TESTCASE( isxdigit('11') == false );
    TESTCASE( isxdigit(9328755) == false );
    TESTCASE( isxdigit('.') == false );
    TESTCASE( isxdigit(']') == false );
    TESTCASE( isxdigit(c) == false );
    TESTCASE( isxdigit(d) == false);
    return TEST_RESULTS;
}

#endif // TEST
