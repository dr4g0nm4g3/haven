/*
    Summary: clampradl.c
    *Definition of domain clipping tools*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <math.h>

#define PI 3.1415926535897932384626433832795028841971L

static long double _HCLIB_doclamppl(long double x, long double clamp);
static long double _HCLIB_doclampnl(long double x, long double clamp);

/* Function: _HCLIB_doclamppl
 * recursively shift x into the domain [0,clamp]
 */
static long double _HCLIB_doclamppl(long double x, long double clamp)
{
    if (clamp < x) x = _HCLIB_doclamppl(x, clamp * 2);
    if (clamp < x) x -= clamp;
    return(x);
}

/* Function: _HCLIB_doclampnl
 * recursively shift x into the domain [-clamp,0]
 */
static long double _HCLIB_doclampnl(long double x, long double clamp)
{
    if (clamp > x) x = _HCLIB_doclampnl(x, clamp * 2);
    if (clamp > x) x -= clamp;
    return(x);

}

/* Function: _HCLIB_clampradl
 * ensure x is in the range [-pi,pi], otherwise shift the domain into position
 */
long double _HCLIB_clampradl(long double x)
{
    if (x > PI)
    {
        x = _HCLIB_doclamppl(x, 2 * PI);
        if (x > PI) x -= (2 * PI);
        return(x);
    } else if (x < -PI) {
        x = _HCLIB_doclampnl(x, -2 * PI);
        if (x < -PI) x += (2 * PI);
        return(x);
    } else {
        return(x);
    }
}
#ifdef TEST
#include <_HCLIB_test.h>

#define MARGIN 0.000000001L
static long double variance (long double v, long double d)
{
    if (v > d) return (v - d);
    return (d - v);
}

int main(void)
{
    BEGIN_TESTS;
    TESTCASE( variance( _HCLIB_clampradl(PI - MARGIN) , PI - MARGIN) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradl(-PI + MARGIN) , -PI + MARGIN) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradl(2*PI) , 0) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradl((-2)*PI) , 0 ) < MARGIN);
    return(TEST_RESULTS);
}

#endif

