/* $Id$ */

/* OS glue functions declaration <_HCLIB_glue.h>

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

/* -------------------------------------------------------------------------- */
/* OS "glue", part 2                                                          */
/* These are the functions you will have to touch, as they are where PDCLib   */
/* interfaces with the operating system.                                      */
/* They operate on data types partially defined by _HCLIB_config.h.          */
/* -------------------------------------------------------------------------- */

/* A system call that terminates the calling process, returning a given status
   to the environment.
*/
void _HCLIB_Exit( int status ) _HCLIB_NORETURN;

/* A system call that adds n pages of memory to the process heap (if n is
   positive), or releases n pages from the process heap (if n is negative).
   Return a (void *) pointing to the *former* end-of-heap if successful, NULL
   otherwise.
*/
void * _HCLIB_allocpages( int n );

/* A system call that opens a file identified by name in a given mode, and
   returns a file descriptor uniquely identifying that file.
*/
_HCLIB_fd_t _HCLIB_open( char const * const filename, unsigned int mode );

/* A system call that writes n characters to a file identified by given file
   descriptor. Return the number of characters actually written, or zero if
   an error occurred.
*/
_HCLIB_size_t _HCLIB_write( _HCLIB_fd_t fd, char const * buffer, _HCLIB_size_t n );

/* A system call that reads n characters into a buffer, from a file identified
   by given file descriptor. Return the number of characters read.
*/
_HCLIB_size_t _HCLIB_read( _HCLIB_fd_t fd, char * buffer, _HCLIB_size_t n );

/* A system call that closes a file identified by given file descriptor. Return
   zero on success, non-zero otherwise.
*/
int _HCLIB_close( _HCLIB_fd_t fd );

/* A system call that removes a file identified by name. Return zero on success,
   non-zero otherwise.
*/
int _HCLIB_remove( const char * filename );

/* A system call that renames a file from given old name to given new name.
   Return zero on success, non-zero otherwise. In case of failure, the file
   must still be accessible by old name.
*/
int _HCLIB_rename( const char * old, const char * new );

/* A system call that returns one if the given file descriptor refers to an
   interactive device, and zero otherwise.
 */
int _HCLIB_isinteractive( _HCLIB_fd_t fd );

/* A platform-specific call that performs comparison between floating point numbers
 */
int _HCLIB_fp_unordered_compare(long double x, long double y);

int _HCLIB_fflush( struct _HCLIB_file_t * stream );

unsigned int _HCLIB_filemode( char const * const mode );

const char * _HCLIB_print( const char * spec, struct _HCLIB_status_t * status );
