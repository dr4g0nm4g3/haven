/*
    Summary: cosl.c
    *Libc implementation of cosl*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */


#include <math.h>

// this should be the smallest integer for which (pi^x)/(x!)  <  2^(-bits_in_mantissa)
#define expansions 35

/* Function: cosl
 * computes and returns the cosine of x (using a taylor expansion)
 */
long double cosl(long double x)
{
    // clamp to [-pi,pi]
    long double clampx = _HCLIB_clampradd(x);

    long double xsquared = clampx * clampx;
    long double toproot = xsquared;
    long double bottomroot = 2;
    int lpc = 2;
    long double cosine = 1;

    while (lpc < expansions)
    {
        cosine -= (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (long double) lpc;
        lpc++; bottomroot *= (long double) lpc;

        cosine += (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (long double) lpc;
        lpc++; bottomroot *= (long double) lpc;
    }

    return(cosine);
}

#ifdef TEST
#include <_HCLIB_test.h>

#define MARGIN 0.000000001L
#define PI 3.1415926535897932384626433832795028841971L

static long double variance (long double v, long double d)
{
    if (v > d) return (v - d);
    return (d - v);
}

int main(void)
{
    BEGIN_TESTS;
    TESTCASE( cosl(0) == 1.0f );
    TESTCASE( variance( cosl(PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( cosl(-PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( cosl(2 * PI) , -1.0f ) < MARGIN  );
    TESTCASE( variance( cosl(-2 * PI) , -1.0f ) < MARGIN  );
    return(TEST_RESULTS);
}

#endif

