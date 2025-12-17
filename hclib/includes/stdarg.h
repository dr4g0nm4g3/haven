/* $Id: stdarg.h 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* 7.15 Variable arguments <stdarg.h> 

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _HCLIB_STDARG_H
#define _HCLIB_STDARG_H _HCLIB_STDARG_H

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

typedef _HCLIB_va_list va_list;

#define va_arg( ap, type )    _HCLIB_va_arg( ap, type )
#define va_copy( dest, src )  _HCLIB_va_copy( dest, src )
#define va_end( ap )          _HCLIB_va_end( ap )
#define va_start( ap, parmN ) _HCLIB_va_start( ap, parmN )

#endif

