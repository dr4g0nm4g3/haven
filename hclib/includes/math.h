/*
 * math.h - header for mathematical functions
 *
 * On domain error, implementation defined value returned and errno set to EDOM
 *  On range error, errno set to ERANGE and return value is HUGE_VAL with correct
 *  sign for overflow or 0 for underflow.
 *  Angles are in radians
 *
 * date: 08/18/2007
 * author: Jeff DiClemente
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

// TODO: implementation

#ifndef _HCLIB_MATH_H
#define _HCLIB_MATH_H _HCLIB_MATH_H

#ifndef _HCLIB_AUX_H
#define _HCLIB_AUX_H _HCLIB_AUX_H
#include <_HCLIB_aux.h>
#endif

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

#ifdef _HCLIB_ERRNO_H
#include <errno.h>
#endif

/* magnitude returned (with correct sign) on overflow error */
#define HUGE_VAL 1.7976931348623157e+308
#define HUGE_VALF 3.40282347e+38F
#define HUGE_VALL 1.18973149535723176508575932662800702e+4932L

/* exponential of x */
float expf(float x);
double exp(double x);
long double expl(long double x);

/* natural logarithm of x */
float logf(float x);
double log(double x);
long double logl(long double x);

/* base 10 logarithm of x */
float log10f(float x);
double log10(double x);
long double log10l(long double x);

float log1pf(float x);
double log1p(double x);
long double log1pl(long double x);

float log2f(float x);
double log2(double x);
long double log2l(long double x);

float logbf(float x);
double logb(double x);
long double logbl(long double x);

/* x raised to power y */
float powf(float x, float y);
double pow(double x, double y);
long double powl(long double x, long double y);

/* square root of x */
float sqrtf(float x);
double sqrt(double x);
long double sqrtl(long double x);

/* smallest integer not less than x */
float ceilf(float x);
double ceil(double x);
long double ceill(long double x);

/* largest integer not greater than x */
float floorf(float x);
double floor(double x);
long double floorl(long double x);

/* absolute value of x */
float fabsf(float x);
double fabs(double x);
long double fabsl(long double x);

/* x times 2 to the power n */
float ldexpf(float x, int e);
double ldexp(double x, int e);
long double ldexpl(long double x, int e);

/* if x non-zero, return value, with absolute value in interval [1/2, 1) and assigns to *exp integer
 * such that product of return value and 2 raised to the power *exp equals x; if x is zero both
 * return value and *exp is zero
 */
float frexpf(float value, int *e);
double frexp(double value, int *e);
long double frexpl(long double value, int *e);

/* returns fractional part of assigns to *ip integral part of x, both with same sign as x */
float modff(float value, float *iptr);
double modf(double value, double *iptr);
long double modfl(long double value, long double *iptr);

float scalbnf(float x, int n);
double scalbn(double x, int n);
long double scalbnl(long double x, int n);

float scalblnf(float x, long int n);
double scalbln(double x, long int n);
long double scalblnl(long double x, long int n);

/* if y non-zero, floating point remainder of x/y with same sign as x; if y is zero result is implementation defined */
float fmodf(float x, float y);
double fmod(double x, double y);
long double fmodl(long double x, long double y);

float remainderf(float x, float y);
double remainder(double x, double y);
long double remainderl(long double x, long double y);

float remquof(float x, float y, int *quo);
double remquo(double x, double y, int *quo);
long double remquol(long double x, long double y, int *quo);

/* sine of x */
double sin(double x);
long double sinl(long double x);
float sinf(float x);

/* cosine of x */
double cos(double x);
long double cosl(long double x);
float cosf(float x);

/* tangent of x */
double tan(double x);

/* arc-sine of x */
float asinf(float x);
double asin(double x);
long double asinl(long double x);

/* arc-cosine of x */
float acosf(float x);
double acos(double x);
long double acosl(long double x);

/* arc-tangent of x */
float atanf(float x);
double atan(double x);
long double atanl(long double x);

/* arc tangent of x/y */
float atan2f(float y, float x);
double atan2(double y, double x);
long double atan2l(long double y, long double x);

/* hyperbolic sine of x */
float sinhf(float x);
double sinh(double x);
long double sinhl(long double x);

/* hyperbolic cosine of x */
float coshf(float x);
double cosh(double x);
long double coshl(long double x);

/* hyperbolic tangent of x */
float tanhf(float x);
double tanh(double x);
long double tanhl(long double x);

float nearbyintf(float x);
double nearbyint(double x);
long double nearbyintl(long double x);

float rintf(float x);
double rint(double x);
long double rintl(long double x);

long int lrintf(float x);
long int lrint(double x);
long int lrintl(long double x);

long long int llrintf(float x);
long long int llrint(double x);
long long int llrintl(long double x);

float roundf(float x);
double round(double x);
long double roundl(long double x);

long int lroundf(float x);
long int lround(double x);
long int lroundl(long double x);

long long int llroundf(float x);
long long int llround(double x);
long long int llroundl(long double x);

float truncf(float x);
double trunc(double x);
long double truncl(long double x);

/* helper functions */
float _HCLIB_clampradf(float x);
double _HCLIB_clampradd(double x);
long double _HCLIB_clampradl(long double x);

#endif /* _HCLIB_MATH_H */
