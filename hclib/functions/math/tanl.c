/*
    Summary: tanl.c
    *Libc implementation of tanl*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <math.h>

/* Function: tanl
 * computes the tangent of angle x
 */
long double tanl(long double x)
{
    x = _HCLIB_clampradl(x);
    return (sinl(x) / cosl(x));
}
