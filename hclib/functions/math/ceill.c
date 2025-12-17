/*
    Summary: ceill.c
    *Libc implementation of ceill*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>
#include <stdint.h>

/* Function: ceill
 * gets and returns the integer value of x when rounded up.
 */
long double ceill(long double x)
{
    long double copy = truncl(x);
    if (copy < x) return (x + 1);
    return(copy);
}

