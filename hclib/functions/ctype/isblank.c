/*
        Summary: isblank.c
        *implementation of the libc isblank call*
        
        manually added to pdclib

        Author:
            Marcel Sondaar

        Licence:
            Public Domain
*/

#include <ctype.h>
#include <stdbool.h>

/* Function: isblank
   Returns nonzero when c is a blank (either space or tab) */

int isblank(int c)
{
    if(c == ' ') return(true);
    if(c == '\t') return(true);
    return(false);
}

#ifdef TEST
#include <_HCLIB_test.h>

int main(void)
{
    BEGIN_TESTS;
    TESTCASE( isblank(0x0) == false);
    TESTCASE( isblank(' ') == true);
    TESTCASE( isblank(0x7) == false);
    TESTCASE( isblank('\t') == true);
    TESTCASE( isblank('0') == false);
    TESTCASE( isblank('a') == false);
    TESTCASE( isblank('A') == false);
    TESTCASE( isblank('Z') == false);
    return(TEST_RESULTS);
}

#endif
