/* $Id: _HCLIB_int.h 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* PDCLib internal integer logic <_HCLIB_int.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* You should not have to edit anything in this file; if you DO have to, it   */
/* would be considered a bug / missing feature: notify the author(s).         */
/* -------------------------------------------------------------------------- */

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

#ifndef _HCLIB_AUX_H
#define _HCLIB_AUX_H _HCLIB_AUX_H
#include <_HCLIB_aux.h>
#endif

/* null pointer constant */
#define _HCLIB_NULL 0

/* -------------------------------------------------------------------------- */
/* Limits of native datatypes                                                 */
/* -------------------------------------------------------------------------- */
/* The definition of minimum limits for unsigned datatypes is done because    */
/* later on we will "construct" limits for other abstract types:              */
/* USHRT -> _HCLIB_ + USHRT + _MIN -> _HCLIB_USHRT_MIN -> 0                 */
/* INT -> _HCLIB_ + INT + _MIN -> _HCLIB_INT_MIN -> ... you get the idea.   */
/* -------------------------------------------------------------------------- */

/* Setting 'char' limits                                                      */
#define _HCLIB_CHAR_BIT    8
#define _HCLIB_UCHAR_MIN   0
#define _HCLIB_UCHAR_MAX   0xff
#define _HCLIB_SCHAR_MIN   (-0x7f - 1)
#define _HCLIB_SCHAR_MAX   0x7f
#ifdef  _HCLIB_CHAR_SIGNED
#define _HCLIB_CHAR_MIN    _HCLIB_SCHAR_MIN
#define _HCLIB_CHAR_MAX    _HCLIB_SCHAR_MAX
#else
#define _HCLIB_CHAR_MIN    0
#define _HCLIB_CHAR_MAX    _HCLIB_UCHAR_MAX
#endif

/* Setting 'short' limits                                                     */
#if     _HCLIB_SHRT_BYTES == 2
#define _HCLIB_SHRT_MAX      0x7fff
#define _HCLIB_SHRT_MIN      (-0x7fff - 1)
#define _HCLIB_USHRT_MAX     0xffff
#else
#error Unsupported width of 'short' (not 16 bit).
#endif
#define _HCLIB_USHRT_MIN 0

#if _HCLIB_INT_BYTES < _HCLIB_SHRT_BYTES
#error Bogus setting: short > int? Check _HCLIB_config.h.
#endif

/* Setting 'int' limits                                                       */
#if     _HCLIB_INT_BYTES == 2
#define _HCLIB_INT_MAX   0x7fff
#define _HCLIB_INT_MIN   (-0x7fff - 1)
#define _HCLIB_UINT_MAX  0xffffU
#elif   _HCLIB_INT_BYTES == 4
#define _HCLIB_INT_MAX   0x7fffffff
#define _HCLIB_INT_MIN   (-0x7fffffff - 1)
#define _HCLIB_UINT_MAX  0xffffffffU
#elif _HCLIB_INT_BYTES   == 8
#define _HCLIB_INT_MAX   0x7fffffffffffffff
#define _HCLIB_INT_MIN   (-0x7fffffffffffffff - 1)
#define _HCLIB_UINT_MAX  0xffffffffffffffff
#else
#error Unsupported width of 'int' (neither 16, 32, nor 64 bit).
#endif
#define _HCLIB_UINT_MIN 0

/* Setting 'long' limits                                                      */
#if   _HCLIB_LONG_BYTES   == 4
#define _HCLIB_LONG_MAX   0x7fffffffL
#define _HCLIB_LONG_MIN   (-0x7fffffffL - 1L)
#define _HCLIB_ULONG_MAX  0xffffffffUL
#elif   _HCLIB_LONG_BYTES == 8
#define _HCLIB_LONG_MAX   0x7fffffffffffffffL
#define _HCLIB_LONG_MIN   (-0x7fffffffffffffffL - 1L)
#define _HCLIB_ULONG_MAX  0xffffffffffffffffUL
#else
#error Unsupported width of 'long' (neither 32 nor 64 bit).
#endif
#define _HCLIB_ULONG_MIN 0

/* Setting 'long long' limits                                                 */
#if _HCLIB_LLONG_BYTES    == 8
#define _HCLIB_LLONG_MAX  0x7fffffffffffffffLL
#define _HCLIB_LLONG_MIN  (-0x7fffffffffffffffLL - 1LL)
#define _HCLIB_ULLONG_MAX 0xffffffffffffffffULL
#elif _HCLIB_LLONG_BYTES  == 16
#define _HCLIB_LLONG_MAX  0x7fffffffffffffffffffffffffffffffLL
#define _HCLIB_LLONG_MIN  (-0x7fffffffffffffffffffffffffffffffLL - 1LL)
#define _HCLIB_ULLONG_MAX 0xffffffffffffffffffffffffffffffffLL
#else
#error Unsupported width of 'long long' (neither 64 nor 128 bit).
#endif
#define _HCLIB_ULLONG_MIN 0

/* -------------------------------------------------------------------------- */
/* <stdint.h> exact-width types and their limits                              */
/* -------------------------------------------------------------------------- */

/* Setting 'int8_t', its limits, and its literal.                             */
#if     _HCLIB_CHAR_BIT == 8
typedef signed char        _HCLIB_int8_t;
typedef unsigned char      _HCLIB_uint8_t;
#define _HCLIB_INT8_MAX   _HCLIB_CHAR_MAX
#define _HCLIB_INT8_MIN   _HCLIB_CHAR_MIN
#define _HCLIB_UINT8_MAX  _HCLIB_UCHAR_MAX
#define _HCLIB_INT8_LITERAL
#define _HCLIB_UINT8_LITERAL
#else
#error Unsupported width of char (not 8 bits).
#endif

/* Setting 'int16_t', its limits, and its literal                             */
#if     _HCLIB_INT_BYTES  == 2
typedef signed int         _HCLIB_int16_t;
typedef unsigned int       _HCLIB_uint16_t;
#define _HCLIB_INT16_MAX  _HCLIB_INT_MAX
#define _HCLIB_INT16_MIN  _HCLIB_INT_MIN
#define _HCLIB_UINT16_MAX _HCLIB_UINT_MAX
#define _HCLIB_INT16_LITERAL
#define _HCLIB_UINT16_LITERAL
#elif   _HCLIB_SHRT_BYTES == 2
typedef signed short       _HCLIB_int16_t;
typedef unsigned short     _HCLIB_uint16_t;
#define _HCLIB_INT16_MAX  _HCLIB_SHRT_MAX
#define _HCLIB_INT16_MIN  _HCLIB_SHRT_MIN
#define _HCLIB_UINT16_MAX _HCLIB_USHRT_MAX
#define _HCLIB_INT16_LITERAL  s
#define _HCLIB_UINT16_LITERAL us
#else
#error Neither 'short' nor 'int' are 16-bit.
#endif

/* Setting 'int32_t', its limits, and its literal                             */
#if     _HCLIB_INT_BYTES  == 4
typedef signed int         _HCLIB_int32_t;
typedef unsigned int       _HCLIB_uint32_t;
#define _HCLIB_INT32_MAX  _HCLIB_INT_MAX
#define _HCLIB_INT32_MIN  _HCLIB_INT_MIN
#define _HCLIB_UINT32_MAX _HCLIB_UINT_MAX
#define _HCLIB_INT32_LITERAL
#define _HCLIB_UINT32_LITERAL
#elif   _HCLIB_LONG_BYTES == 4
typedef signed long        _HCLIB_int32_t;
typedef unsigned long      _HCLIB_uint32_t;
#define _HCLIB_INT32_MAX  _HCLIB_LONG_MAX
#define _HCLIB_INT32_MIN  _HCLIB_LONG_MIN
#define _HCLIB_UINT32_MAX _HCLIB_LONG_MAX
#define _HCLIB_INT32_LITERAL  l
#define _HCLIB_UINT32_LITERAL ul
#else
#error Neither 'int' nor 'long' are 32-bit.
#endif

#if     _HCLIB_LONG_BYTES == 8
typedef signed long        _HCLIB_int64_t;
typedef unsigned long      _HCLIB_uint64_t;
#define _HCLIB_INT64_MAX  _HCLIB_LONG_MAX
#define _HCLIB_INT64_MIN  _HCLIB_LONG_MIN
#define _HCLIB_UINT64_MAX  _HCLIB_ULONG_MAX
#define _HCLIB_INT64_LITERAL  l
#define _HCLIB_UINT64_LITERAL ul
#elif _HCLIB_LLONG_BYTES  == 8
typedef signed long long   _HCLIB_int64_t;
typedef unsigned long long _HCLIB_uint64_t;
#define _HCLIB_INT64_MAX  _HCLIB_LLONG_MAX
#define _HCLIB_INT64_MIN  _HCLIB_LLONG_MIN
#define _HCLIB_UINT64_MAX  _HCLIB_ULLONG_MAX
#define _HCLIB_INT64_LITERAL  ll
#define _HCLIB_UINT64_LITERAL ull
#else
#error Neither 'long' nor 'long long' are 64-bit.
#endif

/* -------------------------------------------------------------------------- */
/* <stdint.h> "fastest" types and their limits                                */
/* -------------------------------------------------------------------------- */
/* This is, admittedly, butt-ugly. But at least it's ugly where the average   */
/* user of PDCLib will never see it, and makes <_HCLIB_config.h> much        */
/* cleaner.                                                                   */
/* -------------------------------------------------------------------------- */

typedef _HCLIB_fast8          _HCLIB_int_fast8_t;
typedef unsigned _HCLIB_fast8 _HCLIB_uint_fast8_t;
#define _HCLIB_INT_FAST8_MIN  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_FAST8 ), _MIN )
#define _HCLIB_INT_FAST8_MAX  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_FAST8 ), _MAX )
#define _HCLIB_UINT_FAST8_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_U, _HCLIB_FAST8 ), _MAX )

typedef _HCLIB_fast16          _HCLIB_int_fast16_t;
typedef unsigned _HCLIB_fast16 _HCLIB_uint_fast16_t;
#define _HCLIB_INT_FAST16_MIN  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_FAST16 ), _MIN )
#define _HCLIB_INT_FAST16_MAX  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_FAST16 ), _MAX )
#define _HCLIB_UINT_FAST16_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_U, _HCLIB_FAST16 ), _MAX )

typedef _HCLIB_fast32          _HCLIB_int_fast32_t;
typedef unsigned _HCLIB_fast32 _HCLIB_uint_fast32_t;
#define _HCLIB_INT_FAST32_MIN  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_FAST32 ), _MIN )
#define _HCLIB_INT_FAST32_MAX  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_FAST32 ), _MAX )
#define _HCLIB_UINT_FAST32_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_U, _HCLIB_FAST32 ), _MAX )

typedef _HCLIB_fast64          _HCLIB_int_fast64_t;
typedef unsigned _HCLIB_fast64 _HCLIB_uint_fast64_t;
#define _HCLIB_INT_FAST64_MIN  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_FAST64 ), _MIN )
#define _HCLIB_INT_FAST64_MAX  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_FAST64 ), _MAX )
#define _HCLIB_UINT_FAST64_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_U, _HCLIB_FAST64 ), _MAX )

/* -------------------------------------------------------------------------- */
/* Various <stddef.h> typedefs and limits                                     */
/* -------------------------------------------------------------------------- */

typedef _HCLIB_ptrdiff     _HCLIB_ptrdiff_t;
#define _HCLIB_PTRDIFF_MIN _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_PTRDIFF ), _MIN )
#define _HCLIB_PTRDIFF_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_PTRDIFF ), _MAX )

#define _HCLIB_SIG_ATOMIC_MIN _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_SIG_ATOMIC ), _MIN )
#define _HCLIB_SIG_ATOMIC_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_SIG_ATOMIC ), _MAX )

typedef _HCLIB_size     _HCLIB_size_t;
#define _HCLIB_SIZE_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_SIZE ), _MAX )

typedef _HCLIB_wchar     _HCLIB_wchar_t;
#define _HCLIB_WCHAR_MIN _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_WCHAR ), _MIN )
#define _HCLIB_WCHAR_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_WCHAR ), _MAX )

typedef _HCLIB_wint      _HCLIB_wint_t;
#define _HCLIB_WINT_MIN _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_WINT ), _MIN )
#define _HCLIB_WINT_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_WINT ), _MAX )

typedef _HCLIB_intptr          _HCLIB_intptr_t;
typedef unsigned _HCLIB_intptr _HCLIB_uintptr_t;
#define _HCLIB_INTPTR_MIN  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_INTPTR ), _MIN )
#define _HCLIB_INTPTR_MAX  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_INTPTR ), _MAX )
#define _HCLIB_UINTPTR_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_U, _HCLIB_INTPTR ), _MAX )

typedef _HCLIB_intmax          _HCLIB_intmax_t;
typedef unsigned _HCLIB_intmax _HCLIB_uintmax_t;
#define _HCLIB_INTMAX_MIN  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_INTMAX ), _MIN )
#define _HCLIB_INTMAX_MAX  _HCLIB_concat( _HCLIB_concat( _HCLIB_, _HCLIB_INTMAX ), _MAX )
#define _HCLIB_UINTMAX_MAX _HCLIB_concat( _HCLIB_concat( _HCLIB_U, _HCLIB_INTMAX ), _MAX )
#define _HCLIB_INTMAX_C( value )  _HCLIB_concat( value, _HCLIB_INTMAX_LITERAL )
#define _HCLIB_UINTMAX_C( value ) _HCLIB_concat( value, _HCLIB_concat( u, _HCLIB_INTMAX_LITERAL ) )

/* -------------------------------------------------------------------------- */
/* Various <stdio.h> internals                                                */
/* -------------------------------------------------------------------------- */

/* Flags for representing mode (see fopen()). Note these must fit the same
   status field as the _IO?BF flags in <stdio.h> and the internal flags below.
*/
#define _HCLIB_FREAD    8u
#define _HCLIB_FWRITE   16u
#define _HCLIB_FAPPEND  32u
#define _HCLIB_FRW      64u
#define _HCLIB_FBIN    128u

/* Internal flags, made to fit the same status field as the flags above. */
#define _HCLIB_LIBBUFFER    512u
#define _HCLIB_VIRGINSTR   1024u
#define _HCLIB_ERRORFLAG   2048u
#define _HCLIB_EOFFLAG     4096u
#define _HCLIB_WIDESTREAM  8192u
#define _HCLIB_BYTESTREAM 	16384u
#define _HCLIB_WROTELAST 	32768u

struct _HCLIB_file_t
{
    _HCLIB_fd_t            handle;   /* OS-specific file descriptor */
    _HCLIB_fpos_t          position; /* file position indicator */
    char *                  buffer;   /* file buffer */
    _HCLIB_size_t          bufsize;  /* size of buffer */
    _HCLIB_size_t          bufidx;   /* index to point of action in buffer */
    _HCLIB_size_t          bufend;   /* index to end of pre-read buffer */
    unsigned int            status;   /* misc. status bits */
    struct _HCLIB_file_t * next;     /* provisions for linked list handling */
};

/* -------------------------------------------------------------------------- */
/* Declaration of helper functions (implemented in functions/_HCLIB).        */
/* -------------------------------------------------------------------------- */

/* This is the main function called by atoi(), atol() and atoll().            */
_HCLIB_intmax_t _HCLIB_atomax( const char * s );

/* Two helper functions used by strtol(), strtoul() and long long variants.   */
const char * _HCLIB_strtox_prelim( const char * p, char * sign, int * base );
_HCLIB_uintmax_t _HCLIB_strtox_main( const char ** p, unsigned int base, _HCLIB_uintmax_t error, _HCLIB_uintmax_t limval, _HCLIB_uintmax_t limdigit, char * sign );

/* Digits array used by various integer conversion functions in <stdlib.h>    */
extern char _HCLIB_digits[];
extern char _HCLIB_Xdigits[];

/* Status structure required by _HCLIB_print(). */
struct _HCLIB_status_t
{
    int              base;  /* base to which the value shall be converted    */
    _HCLIB_int_fast32_t flags; /* flags and length modifiers                */
    _HCLIB_size_t   n;     /* maximum number of characters to be written    */
    _HCLIB_size_t   i;     /* number of characters already written          */
    _HCLIB_size_t   this;  /* output chars in the current conversion        */
    char *           s;     /* target buffer                                 */
    _HCLIB_size_t   width; /* width of current field                        */
    _HCLIB_size_t   prec;  /* precision of current field                    */
    struct _HCLIB_file_t * stream;/* for to-stream output                   */
    _HCLIB_va_list  arg;   /* argument stack passed to the printf function  */
};

/* -------------------------------------------------------------------------- */
/* Internal data types                                                        */
/* -------------------------------------------------------------------------- */

/* Structure required by both atexit() and exit() for handling atexit functions */
struct _HCLIB_exitfunc_t
{
    struct _HCLIB_exitfunc_t * next;
    void (*func)( void );
};

/* Structures required by malloc(), realloc(), and free(). */
struct _HCLIB_headnode_t
{
    struct _HCLIB_memnode_t * first;
    struct _HCLIB_memnode_t * last;
};

struct _HCLIB_memnode_t
{
    _HCLIB_size_t size;
    struct _HCLIB_memnode_t * next;
};
