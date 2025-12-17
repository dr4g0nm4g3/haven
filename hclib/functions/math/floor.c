/*
    Summary: floor.c
    *Libc implementation of floor*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>

/* Function: floor
 * gets and returns the integer value of x when rounded down.
 */
double floor(double x)
{
    double copy = trunc(x);
    if (copy > x) return (x - 1);
    return(copy);
}

