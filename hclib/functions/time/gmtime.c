/*
 * gmtime.c
 *
 *  Created on: Oct 3, 2009
 *      Author: dragon
 */

#include <time.h>

struct tm * gmtime(const time_t * tp)
{	//TODO: implement
	return (struct tm *)0;
}

#ifdef TEST
#include <_HCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    return TEST_RESULTS;
}

#endif // TEST
