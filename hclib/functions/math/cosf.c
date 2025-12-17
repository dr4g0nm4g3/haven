/*
    Summary: cosf.c
    *Libc implementation of cosf*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */


#include <math.h>

#define expansions 20

/* Function: cosf
 * computes and returns the cosine of x (using a taylor expansion)
 */
float cosf(float x)
{
    // clamp to [-pi,pi]
    float clampx = _HCLIB_clampradf(x);

    float xsquared = clampx * clampx;
    float toproot = xsquared;
    float bottomroot = 2;
    int lpc = 2;
    float cosine = 1;

    while (lpc < expansions)
    {
        cosine -= (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (float) lpc;
        lpc++; bottomroot *= (float) lpc;

        cosine += (toproot / bottomroot);
        toproot *= xsquared;
        lpc++; bottomroot *= (float) lpc;
        lpc++; bottomroot *= (float) lpc;
    }

    return(cosine);
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
    TESTCASE( cosf(0) == 1.0f );
    TESTCASE( variance( cosf(PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( cosf(-PI) , 0.0f ) < MARGIN  );
    TESTCASE( variance( cosf(2 * PI) , -1.0f ) < MARGIN  );
    TESTCASE( variance( cosf(-2 * PI) , -1.0f ) < MARGIN  );
    return(TEST_RESULTS);
}

#endif
