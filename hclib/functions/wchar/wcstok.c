/*
    Summary: wcstok.c
    *The libc implementation*

    Author:
        Marcel Sondaar

    License:
        Public Domain
*/

/* wcstok( wchar_t *, const wchar_t *, wchar_t **)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <wchar.h>

#ifndef REGTEST

/* Function: wcstok
   Split s1 on each and any character in s2
   Supply NULL to continue searching the previous string.
   ptr must point to a user-provided wchar_t pointer which must be kept the same across calls.

   Returns a pointer to the next null terminated string which was separated by characters occurring in s2

   Returns NULL if there are no more tokens

*/


wchar_t * wcstok( wchar_t * _HCLIB_restrict s1, const wchar_t * _HCLIB_restrict s2, wchar_t ** _HCLIB_restrict ptr)
{
    const wchar_t * p = s2;

    if ( s1 != NULL )
    {
        /* new string */
        *ptr = s1;
    }
    else
    {
        /* old string continued */
        if ( *ptr == NULL )
        {
            /* No old string, no new string, nothing to do */
            return NULL;
        }
        s1 = *ptr;
    }

    /* skipping leading s2 characters */
    while ( *p && *s1 )
    {
        if ( *s1 == *p )
        {
            /* found seperator; skip and start over */
            ++s1;
            p = s2;
            continue;
        }
        ++p;
    }

    if ( ! *s1 )
    {
        /* no more to parse */
        return ( *ptr = NULL );
    }

    /* skipping non-s2 characters */
    *ptr = s1;
    while ( **ptr )
    {
        p = s2;
        while ( *p )
        {
            if ( **ptr == *p++ )
            {
                /* found seperator; overwrite with '\0', position *ptr, return */
                **ptr++ = '\0';
                return s1;
            }
        }
        ++*ptr;
    }

    /* parsed to end of string */
    return ( *ptr = NULL );
}

#endif

#ifdef TEST
#include <_HCLIB_test.h>

#endif
