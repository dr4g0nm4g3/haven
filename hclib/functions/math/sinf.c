/*
    Summary: sinf.c
    *Libc implementation of sinf*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */


#include <math.h>

#define expansions 20

/* Function: sinf
 * computes and returns the sine of x (using a taylor expansion)
 */
float sinf(float x)
{
    // clamp to [-pi,pi]
    float clampx = _HCLIB_clampradf(x);

    float xsquared = clampx * clampx;
    float toproot = clampx;
    float bottomroot = 1;
    int lpc = 1;
    float sine = 0;

    while (lpc < expansions)
    {
        sine += (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (float) lpc;
        lpc++; bottomroot *= (float) lpc;

        sine -= (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (float) lpc;
        lpc++; bottomroot *= (float) lpc;
    }

    return(sine);
}


#ifdef TEST
#include <_HCLIB_test.h>

#define MARGIN 0.0001L
#define PI 3.1415926535897932384626433832795028841971L

static float variance (float v, float d)
{
    if (v > d) return (v - d);
    return (d - v);
}

int main(void)
{
    BEGIN_TESTS;
    TESTCASE( sinf(0) == 0.0f );
    TESTCASE( variance( sinf(PI) , 1.0f ) < MARGIN  );
    TESTCASE( variance( sinf(-PI) , -1.0f ) < MARGIN  );
    TESTCASE( variance( sinf(2 * PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( sinf(-2 * PI) , 0.0f ) < MARGIN  );
    return(TEST_RESULTS);
}

#endif
