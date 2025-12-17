/*
    Summary: clampradf.c
    *Definition of domain clipping tools*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <math.h>

#define PI 3.1415926535897932384626433832795028841971L

static float _HCLIB_doclampnf(float x, float clamp);
static float _HCLIB_doclamppf(float x, float clamp);

/* Function: _HCLIB_doclamppf
 * recursively shift x into the domain [0,clamp]
 */
static float _HCLIB_doclamppf(float x, float clamp)
{
    if (clamp < x) x = _HCLIB_doclamppf(x, clamp * 2);
    if (clamp < x) x -= clamp;
    return(x);
}

/* Function: _HCLIB_doclampnf
 * recursively shift x into the domain [-clamp,0]
 */
static float _HCLIB_doclampnf(float x, float clamp)
{
    if (clamp > x) x = _HCLIB_doclampnf(x, clamp * 2);
    if (clamp > x) x -= clamp;
    return(x);

}

/* Function: _HCLIB_clampradf
 * ensure x is in the range [-pi,pi], otherwise shift the domain into position
 */
float _HCLIB_clampradf(float x)
{
    if (x > PI)
    {
        x = _HCLIB_doclamppf(x, 2 * PI);
        if (x > PI) x -= (2 * PI);
        return(x);
    } else if (x < -PI) {
        x = _HCLIB_doclampnf(x, -2 * PI);
        if (x < -PI) x += (2 * PI);
        return(x);
    } else {
        return(x);
    }
}

#ifdef TEST
#include <_HCLIB_test.h>

#define MARGIN 0.0001L
static float variance (float v, float d)
{
    if (v > d) return (v - d);
    return (d - v);
}

int main(void)
{
    BEGIN_TESTS;
    TESTCASE( variance( _HCLIB_clampradf(PI - MARGIN) , PI - MARGIN) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradf(-PI + MARGIN) , - PI + MARGIN) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradf(2*PI) , 0) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradf((-2)*PI) , 0 ) < MARGIN);
    return(TEST_RESULTS);
}

#endif

