/*
    Summary: truncl.c
    *Libc implementation of truncl*

    Author:
        Marcel Sondaar

    License:
        Public Domain

 */

#include <float.h>
#include <math.h>
#include <stdint.h>
/*
#define impliedintbit 1L
#define exponentshift ( LDBL_MANT_DIG - impliedintbit )
#define exponentmask ( ((unsigned __int80) ( (1L << ((unsigned __int80) (sizeof(long double) * 8L - 1L - exponentshift) )) - 1L)) << ((unsigned __int80) exponentshift) )
#define exponentbias 1023L
*/
/* Function: truncl
 * gets and returns the integer part of x
 */
long double truncl(long double x)
{
    // note: works only on systems that use ieee float, since it uses its binary representation
    long double copy = x;
    /*unsigned __int128 * raw = (unsigned __int128 *) &copy;

    unsigned __int128 exponent = ((*raw) & exponentmask) >> exponentshift ;

    if (exponent < exponentbias ) return(0);
    if (exponent >= exponentbias + exponentshift ) return(x);

    *raw = *raw & (0xffffffffffffffffffff << (exponentbias + exponentshift - exponent));
*/
    return(copy);
}

