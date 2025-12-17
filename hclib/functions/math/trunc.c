/*
    Summary: trunc.c
    *Libc implementation of trunc*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>
#include <stdint.h>

#define impliedintbit 1L
#define exponentshift ( DBL_MANT_DIG - impliedintbit )
#define exponentmask ( ((uint64_t) ( (1L << ((uint64_t) (sizeof(double) * 8L - 1L - exponentshift) )) - 1L)) << ((uint64_t) exponentshift) )
#define exponentbias 1023L

/* Function: trunc
 * gets and returns the integer part of x
 */
double trunc(double x)
{
    // note: works only on systems that use ieee float, since it uses its binary representation
    
    union {
        double d;
	uint64_t raw;
    } value;
    
    value.d = x;

    uint64_t exponent = ((value.raw) & exponentmask) >> exponentshift ;

    if (exponent < exponentbias ) return(0);
    if (exponent >= exponentbias + exponentshift ) return(x);

    value.raw = value.raw & (UINT64_MAX << (exponentbias + exponentshift - exponent));

    return(value.d);
}

