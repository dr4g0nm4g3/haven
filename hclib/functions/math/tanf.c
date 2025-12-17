/*
    Summary: tanf.c
    *Libc implementation of tanf*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <math.h>

/* Function: tanf
 * computes the tangent of angle x
 */
float tanf(float x)
{
    x = _HCLIB_clampradf(x);
    return (sinf(x) / cosf(x));
}

