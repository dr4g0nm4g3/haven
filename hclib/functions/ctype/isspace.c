/*
 *
 * int isspace(int ch) - tests whether the character is a whitespace character
 *           			(space, tab, carriage return, new line, vertical tab, formfeed)
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int isspace(int ch)
{
	if(ch == ' ')
		return true;

	if(ch == '\t')
		return true;

	if(ch == '\r')
		return true;

	if(ch == '\n')
		return true;

	// vertical tab
	if(ch == '\v')
		return true;

	// formfeed
	if(ch == '\f')
		return true;

	return false;
}

#endif // REGTEST

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    char space = ' ';
    char tab = '\t';
    TESTCASE( isspace(' ') == true );
    TESTCASE( isspace('Z') == false );
    TESTCASE( isspace('a') == false );
    TESTCASE( isspace(space) == true);
    TESTCASE( isspace('\t') == true );
    TESTCASE( isspace('\r') == true );
    TESTCASE( isspace('\n') == true );
    TESTCASE( isspace(tab) == true);
    return TEST_RESULTS;
}

#endif // TEST
