/*
    Summary: ceil.c
    *Libc implementation of ceil*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>
#include <stdint.h>

/* Function: ceil
 * gets and returns the integer value of x when rounded up.
 */
double ceil(double x)
{
    double copy = trunc(x);
    if (copy < x) return (x + 1);
    return(copy);
}

