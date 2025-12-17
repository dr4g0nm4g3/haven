/*
    Summary: ceilf.c
    *Libc implementation of ceilf*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>
#include <stdint.h>

/* Function: ceilf
 * gets and returns the integer value of x when rounded up.
 */
float ceilf(float x)
{
    float copy = trunc(x);
    if (copy < x) return (x + 1);
    return(copy);
}

