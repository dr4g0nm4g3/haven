/* $Id: _HCLIB_config.h 262 2006-11-16 07:34:57Z solar $ */

/* Release $Name$ */

/* Internal PDCLib configuration <_HCLIB_config.h>
   (Generic Template)

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* -------------------------------------------------------------------------- */
/* Misc                                                                       */
/* -------------------------------------------------------------------------- */

/* The character (sequence) your platform uses as newline.                    */
#define _HCLIB_endl "\n"

/* exit() can signal success to the host environment by the value of zero or  */
/* the constant EXIT_SUCCESS. Failure is signaled by EXIT_FAILURE. Note that  */
/* any other return value is "implementation-defined", i.e. your environment  */
/* is not required to handle it gracefully. Set your definitions here.        */
#define _HCLIB_SUCCESS 0
#define _HCLIB_FAILURE -1

/* qsort() in <stdlib.h> requires a function that swaps two memory areas.     */
/* Below is a naive implementation that can be improved significantly for     */
/* specific platforms, e.g. by swapping int instead of char.                  */
#define _HCLIB_memswp( i, j, size ) char tmp; do { tmp = *i; *i++ = *j; *j++ = tmp; } while ( --size );

/* Define this to some compiler directive that can be written after the       */
/* parameter list of a function declaration to indicate the function does     */
/* never return. If your compiler does not support such a directive, define   */
/* to nothing. (This is to avoid warnings with the exit functions under GCC.) */
#define _HCLIB_NORETURN __attribute__(( noreturn ))

/* -------------------------------------------------------------------------- */
/* Integers                                                                   */
/* -------------------------------------------------------------------------- */
/* Assuming 8-bit char, two's-complement architecture here. 'short' being     */
/* 16 bit, 'int' being either 16, 32 or 64 bit, 'long' being either 32 or 64  */
/* bit (but 64 bit only if 'int' is 32 bit), and 'long long' being 64 bit if  */
/* 'long' is not, 64 or 128 bit otherwise.                                    */
/* Author is quite willing to support other systems but would like to hear of */
/* interest in such support and details on the to-be-supported architecture   */
/* first, before going to lengths about it.                                   */
/* -------------------------------------------------------------------------- */

/* Comment out (or delete) the line below if your 'char' type is unsigned.    */
#define _HCLIB_CHAR_SIGNED 1

/* Width of the integer types short, int, long, and long long, in bytes.      */
/* SHRT == 2, INT >= SHRT, LONG >= INT >= 4, LLONG >= LONG - check your       */
/* compiler manuals.                                                          */
#define _HCLIB_SHRT_BYTES  2
#define _HCLIB_INT_BYTES   4
#define _HCLIB_LONG_BYTES  4
#define _HCLIB_LLONG_BYTES 8

/* <stdlib.h> defines the div() function family that allows taking quotient   */
/* and remainder of an integer division in one operation. Many platforms      */
/* support this in hardware / opcode, and the standard permits ordering of    */
/* the return structure in any way to fit the hardware. That is why those     */
/* structs can be configured here.                                            */

struct _HCLIB_div_t
{
    int quot;
    int rem;
};

struct _HCLIB_ldiv_t
{
    long int quot;
    long int rem;
};

struct _HCLIB_lldiv_t
{
    long long int quot;
    long long int rem;
};

/* -------------------------------------------------------------------------- */
/* <stdint.h> defines a set of integer types that are of a minimum width, and */
/* "usually fastest" on the system. (If, for example, accessing a single char */
/* requires the CPU to access a complete int and then mask out the char, the  */
/* "usually fastest" type of at least 8 bits would be int, not char.)         */
/* If you do not have information on the relative performance of the types,   */
/* the standard allows you to define any type that meets minimum width and    */
/* signedness requirements.                                                   */
/* The defines below are just configuration for the real typedefs and limit   */
/* definitions done in <_HCLIB_int.h>. The uppercase define shall be either  */
/* SHRT, INT, LONG, or LLONG (telling which values to use for the *_MIN and   */
/* *_MAX limits); the lowercase define either short, int, long, or long long  */
/* (telling the actual type to use).                                          */
/* If you require a non-standard datatype to define the "usually fastest"     */
/* types, PDCLib as-is doesn't support that. Please contact the author with   */
/* details on your platform in that case, so support can be added.            */
/* -------------------------------------------------------------------------- */

#define _HCLIB_FAST8 INT
#define _HCLIB_fast8 int

#define _HCLIB_FAST16 INT
#define _HCLIB_fast16 int

#define _HCLIB_FAST32 INT
#define _HCLIB_fast32 int

#define _HCLIB_FAST64 LLONG
#define _HCLIB_fast64 long long

/* -------------------------------------------------------------------------- */
/* What follows are a couple of "special" typedefs and their limits. Again,   */
/* the actual definition of the limits is done in <_HCLIB_int.h>, and the    */
/* defines here are merely "configuration". See above for details.            */
/* -------------------------------------------------------------------------- */

/* The result type of substracting two pointers */
#define _HCLIB_ptrdiff int
#define _HCLIB_PTRDIFF INT

/* An integer type that can be accessed as atomic entity (think asynchronous
   interrupts). The type itself is not defined in a freestanding environment,
   but its limits are. (Don't ask.)
*/
#define _HCLIB_SIG_ATOMIC INT

/* Result type of the 'sizeof' operator (must be unsigned) */
#define _HCLIB_size unsigned int
#define _HCLIB_SIZE UINT

/* Large enough an integer to hold all character codes of the largest supported
   locale.
*/
#define _HCLIB_wchar unsigned short
#define _HCLIB_WCHAR USHRT

#define _HCLIB_wint unsigned int
#define _HCLIB_WINT UINT

#define _HCLIB_intptr int
#define _HCLIB_INTPTR INT

/* Largest supported integer type. Implementation note: see _HCLIB_atomax(). */
#define _HCLIB_intmax long long int
#define _HCLIB_INTMAX LLINT
/* You are also required to state the literal suffix for the intmax type      */
#define _HCLIB_INTMAX_LITERAL ll

/* -------------------------------------------------------------------------- */
/* Floating Point                                                             */
/* -------------------------------------------------------------------------- */

/* Whether the implementation rounds toward zero (0), to nearest (1), toward
   positive infinity (2), or toward negative infinity (3). (-1) signifies
   indeterminable rounding, any other value implementation-specific rounding.
*/
#define _HCLIB_FLT_ROUNDS -1

/* Whether the implementation uses exact-width precision (0), promotes float
   to double (1), or promotes float and double to long double (2). (-1)
   signifies indeterminable behaviour, any other value implementation-specific
   behaviour.
*/
#define _HCLIB_FLT_EVAL_METHOD -1

/* "Number of the decimal digits (n), such that any floating-point number in the
   widest supported floating type with p(max) radix (b) digits can be rounded to
   a floating-point number with (n) decimal digits and back again without change
   to the value p(max) log(10)b if (b) is a power of 10, [1 + p(max) log(10)b]
   otherwise."
   64bit IEC 60559 double format (53bit mantissa) is DECIMAL_DIG 17.
   80bit IEC 60559 double-extended format (64bit mantissa) is DECIMAL_DIG 21.
*/
#define _HCLIB_DECIMAL_DIG 17

/* -------------------------------------------------------------------------- */
/* Platform-dependent macros defined by the standard headers.                 */
/* -------------------------------------------------------------------------- */

/* The offsetof macro
   Contract: Expand to an integer constant expression of type size_t, which
   represents the offset in bytes to the structure member from the beginning
   of the structure. If the specified member is a bitfield, behaviour is
   undefined.
   There is no standard-compliant way to do this.
   This implementation casts an integer zero to 'pointer to type', and then
   takes the address of member. This is undefined behaviour but should work on
   most compilers.
*/
#define _HCLIB_offsetof( type, member ) ( (size_t) &( ( (type *) 0 )->member ) )

/* Variable Length Parameter List Handling (<stdarg.h>)
   The macros defined by <stdarg.h> are highly dependent on the calling
   conventions used, and you probably have to replace them with builtins of
   your compiler. The following generic implementation works only for pure
   stack-based architectures, and only if arguments are aligned to pointer
   type. Credits to Michael Moody, who contributed this to the Public Domain.
*/

/* Internal helper macro. va_round is not part of <stdarg.h>. */
#define _HCLIB_va_round( type ) ( (sizeof(type) + sizeof(void *) - 1) & ~(sizeof(void *) - 1) )

typedef char * _HCLIB_va_list;
#define _HCLIB_va_arg( ap, type ) ( (ap) += (_HCLIB_va_round(type)), ( *(type*) ( (ap) - (_HCLIB_va_round(type)) ) ) )
#define _HCLIB_va_copy( dest, src ) ( (dest) = (src), (void)0 )
#define _HCLIB_va_end( ap ) ( (ap) = (void *)0, (void)0 )
#define _HCLIB_va_start( ap, parmN ) ( (ap) = (char *) &parmN + ( _HCLIB_va_round(parmN) ), (void)0 )

/* -------------------------------------------------------------------------- */
/* OS "glue"                                                                  */
/* This is where PDCLib interfaces with the operating system. The examples    */
/* below are POSIX calls; provide your OS' equivalents.                       */
/* -------------------------------------------------------------------------- */

/* A system call that terminates the calling process */
void _exit( int status ) __attribute__(( noreturn ));
#define _HCLIB_Exit( x ) _exit( x )

/* Memory management */

/* Set this to the page size of your OS. If your OS does not support paging, set
   to an appropriate value. (Too small, and malloc() will call the kernel too
   often. Too large, and you will waste memory.
*/
#define _HCLIB_PAGESIZE 4096

/* Set this to the minimum memory node size. Any malloc() for a smaller size
   will be satisfied by a malloc() of this size instead.
*/
#define _HCLIB_MINALLOC 8

/* Request another x pages (of size _HCLIB_PAGESIZE) of memory from the kernel,
   or release them back to the kernel if n is negative.
   Return a (void *) pointing to the former end-of-heap if successful, NULL
   otherwise.
*/
void * _HCLIB_allocpages( int n );

/* I/O ---------------------------------------------------------------------- */

/* The unique file descriptor returned by _HCLIB_open(). */
typedef int _HCLIB_fd_t;

/* The value (of type _HCLIB_fd_t) returned by _HCLIB_open() if the operation
   failed.
*/
#define _HCLIB_NOHANDLE -1

/* A type in which to store file offsets. See fgetpos() / fsetpos(). */
typedef struct
{
    int position;
    int parse_state;
} _HCLIB_fpos_t;

/* The default size for file buffers. Must be at least 256. */
#define _HCLIB_BUFSIZ 1024

/* The minimum number of files the implementation can open simultaneously. Must
   be at least 8.
*/
#define _HCLIB_FOPEN_MAX 8

/* Length of the longest filename the implementation guarantees to support. */
#define _HCLIB_FILENAME_MAX 128

/* Buffer size for tmpnam(). */
#define _HCLIB_L_tmpnam 100

/* Number of distinct file names that can be generated by tmpnam(). */
#define _HCLIB_TMP_MAX 50
