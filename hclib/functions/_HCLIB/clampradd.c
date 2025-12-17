/*
    Summary: clampradd.c
    *Definition of domain clipping tools*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <math.h>

#define PI 3.1415926535897932384626433832795028841971L

static double _HCLIB_doclamppd(double x, double clamp);
static double _HCLIB_doclampnd(double x, double clamp);

/* Function: _HCLIB_doclamppl
 * recursively shift x into the domain [0,clamp]
 */
static double _HCLIB_doclamppd(double x, double clamp)
{
    if (clamp < x) x = _HCLIB_doclamppd(x, clamp * 2);
    if (clamp < x) x -= clamp;
    return(x);
}

/* Function: _HCLIB_doclampnd
 * recursively shift x into the domain [-clamp,0]
 */
static double _HCLIB_doclampnd(double x, double clamp)
{
    if (clamp > x) x = _HCLIB_doclampnd(x, clamp * 2);
    if (clamp > x) x -= clamp;
    return(x);

}

/* Function: _HCLIB_clampradd
 * ensure x is in the range [-pi,pi], otherwise shift the domain into position
 */
double _HCLIB_clampradd(double x)
{
    if (x > PI)
    {
        x = _HCLIB_doclamppd(x, 2 * PI);
        if (x > PI) x -= (2 * PI);
        return(x);
    } else if (x < -PI) {
        x = _HCLIB_doclampnd(x, -2 * PI);
        if (x < -PI) x += (2 * PI);
        return(x);
    } else {
        return(x);
    }
}

#ifdef TEST
#include <_HCLIB_test.h>

#define MARGIN 0.000001L
static double variance (double v, double d)
{
    if (v > d) return (v - d);
    return (d - v);
}

int main(void)
{
    BEGIN_TESTS;
    TESTCASE( variance( _HCLIB_clampradd(PI-MARGIN) , PI-MARGIN) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradd(-PI+MARGIN) , -PI+MARGIN) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradd(2*PI) , 0) < MARGIN );
    TESTCASE( variance( _HCLIB_clampradd((-2)*PI) , 0 ) < MARGIN);
    return(TEST_RESULTS);
}

#endif
