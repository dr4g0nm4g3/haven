/*
 * setlocale.c
 *
 *  Created on: Aug 1, 2009
 *      Author: Jeff DiClemente
 */

#include <locale.h>

#ifndef REGTEST

char * setlocale(int category, const char * locale)
{	//  TODO: implement
	return (char *)0;
}

#endif // REGTEST

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    return TEST_RESULTS;
}

#endif // TEST
