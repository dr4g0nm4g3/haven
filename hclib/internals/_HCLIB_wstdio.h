/*
    Summary: _HCLIB_wstdio.h
    *The stdio+wchar combined header*

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


#ifndef _HCLIB_WSTDIO_H
#define _HCLIB_WSTDIO_H _HCLIB_WSTDIO_H

#ifndef _HCLIB_STDIO_H
#include <stdio.h>
#endif

#ifndef _HCLIB_WCHAR_H
#include <wchar.h>
#endif

/*
 * 7.24.2
 */

int fwprintf( struct _HCLIB_file_t * _HCLIB_restrict stream, const wchar_t * _HCLIB_restrict format, ... );
int fwscanf( struct _HCLIB_file_t * _HCLIB_restrict stream, const wchar_t * _HCLIB_restrict format, ... );
int wprintf( const wchar_t * _HCLIB_restrict format, ... );
int wscanf( const wchar_t * _HCLIB_restrict format, ... );
int swprintf( wchar_t * _HCLIB_restrict s, const wchar_t * _HCLIB_restrict format, ... );
int swscanf( const wchar_t * _HCLIB_restrict s, const wchar_t * _HCLIB_restrict format, ... );
int vfwprintf( struct _HCLIB_file_t * _HCLIB_restrict stream, const wchar_t * _HCLIB_restrict format, _HCLIB_va_list arg );
int vfwscanf( struct _HCLIB_file_t * _HCLIB_restrict stream, const wchar_t * _HCLIB_restrict format, _HCLIB_va_list arg );
int vswprintf( wchar_t * _HCLIB_restrict s, const wchar_t * _HCLIB_restrict format, _HCLIB_va_list arg );
int vswscanf( const wchar_t * _HCLIB_restrict s, const wchar_t * _HCLIB_restrict format, _HCLIB_va_list arg );
int vwprintf( const wchar_t * _HCLIB_restrict format, _HCLIB_va_list arg );
int vwscanf( const wchar_t * _HCLIB_restrict format, _HCLIB_va_list arg );

/*
 * 7.24.3
 */

wint_t fgetwc( struct _HCLIB_file_t * stream );
wchar_t * fgetws( wchar_t * _HCLIB_restrict s, int n, struct _HCLIB_file_t * _HCLIB_restrict stream );
wint_t fputwc( wint_t c, struct _HCLIB_file_t * stream );
int fputws( const wchar_t * _HCLIB_restrict s, struct _HCLIB_file_t * _HCLIB_restrict stream );
int fwide( struct _HCLIB_file_t * stream , int mode );
wint_t getwc(struct _HCLIB_file_t * stream);
wint_t getwchar(void);
wint_t putwc(wchar_t c, struct _HCLIB_file_t * stream);
wint_t putwchar(wchar_t c);
wint_t ungetwc(wint_t c, struct _HCLIB_file_t * stream);

/*
 * 7.24.6.1
 */

wchar_t btowc(int c);
int wctob(wchar_t c);

#endif
