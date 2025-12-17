/*
    Summary: tan.c
    *Libc implementation of tan*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <math.h>

/* Function: tan
 * computes the tangent of angle x
 */
double tan(double x)
{
    x = _HCLIB_clampradd(x);
    return (sin(x) / cos(x));
}
