/*
    Summary: floorl.c
    *Libc implementation of floorl*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>

/* Function: floorl
 * gets and returns the integer value of x when rounded down.
 */
long double floorl(long double x)
{
    long double copy = truncl(x);
    if (copy > x) return (x - 1);
    return(copy);
}

