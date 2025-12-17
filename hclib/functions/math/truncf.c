/*
    Summary: truncf.c
    *Libc implementation of truncf*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>
#include <stdint.h>

#define impliedintbit 1L
#define exponentshift ( FLT_MANT_DIG - impliedintbit )
#define exponentmask ( (uint32_t) ( (1L << (sizeof(float) * 8L - 1L - exponentshift) ) - 1L) << ((uint32_t) exponentshift) )
#define exponentbias 127L

/* Function: truncf
 * gets and returns the integer part of x
 */
float truncf(float x)
{
    // note: works only on systems that use ieee float, since it uses its binary representation
    union {
        double d;
	uint32_t raw;
    } value;

    value.d = x;

    uint32_t exponent = ((value.raw) & exponentmask) >> exponentshift ;

    // at exp = 127, the mantissa contains all fractional bits
    // at exp = 127+23, the mantissa contains no bits responsible for the fraction

    if (exponent < exponentbias ) return(0);
    if (exponent >= exponentbias + exponentshift ) return(x);

    value.raw = value.raw & (UINT32_MAX << (exponentbias + exponentshift - exponent));

    return(value.d);
}

