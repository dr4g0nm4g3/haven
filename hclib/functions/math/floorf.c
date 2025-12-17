/*
    Summary: floorf.c
    *Libc implementation of floorf*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>

/* Function: floorf
 * gets and returns the integer value of x when rounded down.
 */
float floorf(float x)
{
    float copy = trunc(x);
    if (copy > x) return (x - 1);
    return(copy);
}

