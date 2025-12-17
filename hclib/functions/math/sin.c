/*
    Summary: sin.c
    *Libc implementation of sinf*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */


#include <math.h>

#define expansions 30

/* Function: sin
 * computes and returns the sine of x (using a taylor expansion)
 */
double sin(double x)
{
    // clamp to [-pi,pi]
    double clampx = _HCLIB_clampradd(x);

    double xsquared = clampx * clampx;
    double toproot = clampx;
    double bottomroot = 1;
    int lpc = 1;
    double sine = 0;

    while (lpc < expansions)
    {
        sine += (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (double) lpc;
        lpc++; bottomroot *= (double) lpc;

        sine -= (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (double) lpc;
        lpc++; bottomroot *= (double) lpc;
    }

    return(sine);
}


#ifdef TEST
#include <_HCLIB_test.h>

#define MARGIN 0.0000001L
#define PI 3.1415926535897932384626433832795028841971L

static double variance (double v, double d)
{
    if (v > d) return (v - d);
    return (d - v);
}

int main(void)
{
    BEGIN_TESTS;
    TESTCASE( sin(0) == 0.0f );
    TESTCASE( variance( sin(PI) , 1.0f ) < MARGIN  );
    TESTCASE( variance( sin(-PI) , -1.0f ) < MARGIN  );
    TESTCASE( variance( sin(2 * PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( sin(-2 * PI) , 0.0f ) < MARGIN  );
    return(TEST_RESULTS);
}

#endif
