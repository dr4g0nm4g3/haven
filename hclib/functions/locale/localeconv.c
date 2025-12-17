/*
 * localeconv.c
 *
 *  Created on: Aug 1, 2009
 *      Author: Jeff DiClemente
 */

#include <locale.h>

#ifndef REGTEST

struct lconv * localeconv(void)
{	// TODO: implement
	return (struct lconv *)0;
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
