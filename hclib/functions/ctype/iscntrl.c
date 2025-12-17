/*
 * int iscntrl(int ch) - tests for a control character (00x0 - 0x1F or 0x7E)
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

#include <ctype.h>
#include <stdbool.h>

#ifndef REGTEST

int iscntrl(int ch)
{	//  (00x0 - 0x1F or 0x7E)
    if((ch <= 31 && ch >= 0) || ch == 126)
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
    char e = '~';
    int i = 0x0;
    int i2 = 0x0;
    int i3 = 0x1;
    int i4 = 0x0A;
    int i5 = 0x0D;
    int i6 = 0x1B;
    BEGIN_TESTS;
    TESTCASE( iscntrl('A') == false );
    TESTCASE( iscntrl('Z') == false );
    TESTCASE( iscntrl('a') == false );
    TESTCASE( iscntrl('z') == false );
    TESTCASE( iscntrl(0) == true );
    TESTCASE( iscntrl(9328755) == false );
    TESTCASE( iscntrl('.') == false );
    TESTCASE( iscntrl(']') == false );
    TESTCASE( iscntrl(c) == false );
    TESTCASE( iscntrl(d) == false );
    TESTCASE( iscntrl(e) == true );
    TESTCASE( iscntrl(i) == true );
    TESTCASE( iscntrl(i2) == true );
    TESTCASE( iscntrl(i3) == true );
    TESTCASE( iscntrl(i4) == true );
    TESTCASE( iscntrl(i5) == true );
    TESTCASE( iscntrl(i6) == true );
    return TEST_RESULTS;
}

#endif // TEST
