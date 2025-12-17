/*
    Summary: sinl.c
    *Libc implementation of sinl*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <math.h>

#define expansions 35

/* Function: sinl
 * computes and returns the sine of x (using a taylor expansion)
 */
long double sinl(long double x)
{
    // clamp to [-pi,pi]
    long double clampx = _HCLIB_clampradl(x);

    long double xsquared = clampx * clampx;
    long double toproot = clampx;
    long double bottomroot = 1;
    int lpc = 1;
    long double sine = 0;

    while (lpc < expansions)
    {
        sine += (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (long double) lpc;
        lpc++; bottomroot *= (long double) lpc;

        sine -= (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (long double) lpc;
        lpc++; bottomroot *= (long double) lpc;
    }

    return(sine);
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
    TESTCASE( sinf(0) == 0.0f );
    TESTCASE( variance( sinl(PI) , 1.0f ) < MARGIN  );
    TESTCASE( variance( sinl(-PI) , -1.0f ) < MARGIN  );
    TESTCASE( variance( sinl(2 * PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( sinl(-2 * PI) , 0.0f ) < MARGIN  );
    return(TEST_RESULTS);
}

#endif
