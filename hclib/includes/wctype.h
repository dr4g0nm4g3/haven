/*
    Summary: wctype.h
    *The libc common definitions header*

    Author:
        Marcel Sondaar

    License:
        Public Domain

*/

/*

   7.25 Wide character classifications and mapping utilities <wctype.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _HCLIB_WCTYPE_H
#define _HCLIB_WCTYPE_H _HCLIB_WCTYPE_H

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

/*
 * 7.25.1
 */

#ifndef _HCLIB_WINT_T_DEFINED
#define _HCLIB_WINT_T_DEFINED _HCLIB_WINT_T_DEFINED
typedef _HCLIB_wint_t   wint_t;
#endif

/* fixme: wctrans_t */
typedef int wctrans_t;

/* fixme: wctype_t */
typedef int wctype_t;

/* missing: WEOF */


/*
 * 7.25.2
 */

int iswalnum(wint_t wc);
int iswalpha(wint_t wc);
int iswblank(wint_t wc);
int iswcntrl(wint_t wc);
int iswdigit(wint_t wc);
int iswgraph(wint_t wc);
int iswlower(wint_t wc);
int iswprint(wint_t wc);
int iswpunct(wint_t wc);
int iswspace(wint_t wc);
int iswupper(wint_t wc);
int iswxdigit(wint_t wc);

int iswctype(wint_t wc, wctype_t desc);
wctype_t wctype(const char * property);

/*
 * 7.25.3
 */

wint_t towlower(wint_t wc);
wint_t towupper(wint_t wc);

wint_t towctrans(wint_t wc, wctype_t desc);
wctrans_t wctrans(const char * property);

#endif

