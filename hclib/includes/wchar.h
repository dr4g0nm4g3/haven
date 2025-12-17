/*
    Summary: wchar.h
    *The libc wide character functions header*

    Author:
        Marcel "(Com)Buster" Sondaar

    License:
        Public Domain

*/

/*

   7.24 Extended multibyte and wide character utilites <wchar.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _HCLIB_WCHAR_H
#define _HCLIB_WCHAR_H _HCLIB_WCHAR_H

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

/*
 *  7.24.1
 */

#ifndef _HCLIB_SIZE_T_DEFINED
#define _HCLIB_SIZE_T_DEFINED _HCLIB_SIZE_T_DEFINED
typedef _HCLIB_size_t size_t;
#endif

#ifndef _HCLIB_WCHAR_T_DEFINED
#define _HCLIB_WCHAR_T_DEFINED _HCLIB_WCHAR_T_DEFINED
typedef _HCLIB_wchar_t wchar_t;
#endif

#ifndef _HCLIB_WINT_T_DEFINED
#define _HCLIB_WINT_T_DEFINED _HCLIB_WINT_T_DEFINED
typedef _HCLIB_wint_t wint_t;
#endif

/* missing:
 * - wint_t
 * - WEOF
 * - struct tm
 * WCHAR_MIN
 * WCHAR_MAX
 */

/* todo: build struct and move it */
typedef int mbstate_t;

#define NULL _HCLIB_NULL


#ifdef _HCLIB_STDIO_H
#include <_HCLIB_wstdio.h>
#endif

/*
 * 7.24.4
 *
 */

double wcstod(const wchar_t * _HCLIB_restrict nptr, wchar_t ** _HCLIB_restrict endptr);
float wcstof(const wchar_t * _HCLIB_restrict nptr, wchar_t ** _HCLIB_restrict endptr);
long double wcstold(const wchar_t * _HCLIB_restrict nptr, wchar_t ** _HCLIB_restrict endptr);
long int wcstol(const wchar_t * _HCLIB_restrict nptr, wchar_t ** _HCLIB_restrict endptr, int base);
long long int wcstoll(const wchar_t * _HCLIB_restrict nptr, wchar_t ** _HCLIB_restrict endptr, int base);
unsigned long int wcstoul(const wchar_t * _HCLIB_restrict nptr, wchar_t ** _HCLIB_restrict endptr, int base);
unsigned long long int wcstoull(const wchar_t * _HCLIB_restrict nptr, wchar_t ** _HCLIB_restrict endptr, int base);

wchar_t * wcscpy(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2);
wchar_t * wcsncpy(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, size_t n);
wchar_t * wmemcpy(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, size_t n);
wchar_t * wmemmove(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, size_t n);

wchar_t * wcscat(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2);
wchar_t * wcsncat(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, size_t n);

int wcscmp(const wchar_t * s1, const wchar_t * s2);
int wcscoll(const wchar_t * s1, const wchar_t * s2);
int wcsncmp(const wchar_t * s1, const wchar_t * s2, size_t n);
size_t wcsxfrm(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, size_t n);
int wmemcmp(const wchar_t * s1, const wchar_t * s2, size_t n);

wchar_t * wcschr(const wchar_t * s, wchar_t c);
size_t wcscspn(const wchar_t * s1, const wchar_t * s2);
wchar_t * wcspbrk(const wchar_t * s1, const wchar_t * s2);
wchar_t * wcsrchr(const wchar_t * s, wchar_t c);
size_t wcsspn(const wchar_t * s1, const wchar_t * s2);
wchar_t * wcsstr(const wchar_t * s1, const wchar_t * s2);
wchar_t * wcstok(wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, wchar_t ** _HCLIB_restrict ptr);
wchar_t * wmemchr(const wchar_t * s, wchar_t c, size_t n);

size_t wcslen(const wchar_t * s);
wchar_t * wmemset(wchar_t * s, wchar_t c, size_t n);

/*
 * 7.24.5
 *
 * missing:
 * wcsftime
 */


/*
 * 7.24.6
 */



int mbsinit(const mbstate_t *ps);

size_t mbrlen(const char * _HCLIB_restrict s, size_t n, mbstate_t * _HCLIB_restrict ps);
size_t mbrtowc(wchar_t * _HCLIB_restrict pwc, const char * _HCLIB_restrict s, size_t n, mbstate_t * _HCLIB_restrict ps);
size_t wcrtomb(char * _HCLIB_restrict s, size_t n, mbstate_t * _HCLIB_restrict ps);

size_t mbsrtowcs(wchar_t * _HCLIB_restrict dst, const char ** _HCLIB_restrict src, size_t len, mbstate_t * _HCLIB_restrict ps);
size_t wcsrotmbs(char * _HCLIB_restrict dst, const wchar_t ** _HCLIB_restrict src, size_t len, mbstate_t * _HCLIB_restrict ps);

#endif

