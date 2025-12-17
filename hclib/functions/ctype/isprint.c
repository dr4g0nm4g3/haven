/*
 * int isprint(int ch) - tests whether the character is a printing character (0x20 - 0x7E)
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int isprint(int ch)
{	// test 0x20 - 0x7E
    if(ch <= 126 && ch >= 32)
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
    TESTCASE( isprint('A') == false );
    TESTCASE( isprint('Z') == false );
    TESTCASE( isprint('a') == false );
    TESTCASE( isprint('z') == false );
    TESTCASE( isprint(0) == false );
    TESTCASE( isprint('9') == false );
    TESTCASE( isprint('11') == false );
    TESTCASE( isprint(9328755) == false );
    TESTCASE( isprint('.') == false );
    TESTCASE( isprint(']') == false );
    TESTCASE( isprint(c) == false );
    TESTCASE( isprint(d) == false);
    return TEST_RESULTS;
}

#endif // TEST
