/*
 * strftime.c
 *
 *  Created on: Oct 3, 2009
 *      Author: dragon
 */

#include <time.h>

size_t strftime(char * s, size_t smax, const char * fmt, const struct tm * tp)
{	//TODO: implement
	return 0;
}

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    return TEST_RESULTS;
}

#endif // TEST
