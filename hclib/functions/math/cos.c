/*
    Summary: cos.c
    *Libc implementation of cos*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */


#include <math.h>

#define expansions 30

/* Function: cos
 * computes and returns the cosine of x (using a taylor expansion)
 */
double cos(double x)
{
    // clamp to [-pi,pi]
    double clampx = _HCLIB_clampradd(x);

    double xsquared = clampx * clampx;
    double toproot = xsquared;
    double bottomroot = 2;
    int lpc = 2;
    double cosine = 1;

    while (lpc < expansions)
    {
        cosine -= (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (double) lpc;
        lpc++; bottomroot *= (double) lpc;

        cosine += (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (double) lpc;
        lpc++; bottomroot *= (double) lpc;
    }

    return(cosine);
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
    TESTCASE( cos(0) == 1.0f );
    TESTCASE( variance( cos(PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( cos(-PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( cos(2 * PI) , -1.0f ) < MARGIN  );
    TESTCASE( variance( cos(-2 * PI) , -1.0f ) < MARGIN  );
    return(TEST_RESULTS);
}

#endif

