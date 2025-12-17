/*
 * ctype.h - function prototypes to test and convert characters
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */
 
#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif
 
#ifndef _HCLIB_CTYPE_H
#define _HCLIB_CTYPE_H _HCLIB_CTYPE_H

// defines common definitions like NULL
#include <stddef.h>

//***************************************************************************
//                             Test Functions
//***************************************************************************
// isalnum - tests whether the character is a letter (A-Z, a-z)
//           or number (0-9)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int isalnum(int ch);

// isalpha - tests whether the character is a letter (A-Z, a-z)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int isalpha(int ch);

// iscntrl - tests whether the character is a control character (00x0 - 0x1F or 0x7E)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int iscntrl(int ch);

// isdigit - tests whether the character is a number (0-9)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int isdigit(int ch);

// isgraph - tests whether the character is a printing character (except space)
//           (0x21 - 0x7E)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int isgraph(int ch);

// islower - tests whether the character is a lowercase letter (a-z)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int islower(int ch);

// isprint - tests whether the character is a printing character (0x20 - 0x7E)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int isprint(int ch);

// ispunct - tests whether the character is a punctuation character
//           (any printing character except space or isalnum)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int ispunct(int ch);

// isspace - tests whether the character is a whitespace character
//           (space, tab, carriage return, new line, vertical tab, formfeed)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int isspace(int ch);

// isupper - tests whether the character is an uppercase letter (A-Z)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int isupper(int ch);

// isxdigit - tests whether the character is a hexadecimal digit (0-9, A-F)
//
//@param  ch - character to test
//@return nonzero for success
//        zero for failure
int isxdigit(int ch);

//***************************************************************************
//						Conversion Functions
//***************************************************************************
// tolower - converts the character, assuming its a letter, to lowercase
//
//@param  ch - character to convert
//@return the changed character on success
//        the character unchanged on failure
int tolower(int ch);

// toupper - converts the character, assuming its a letter to uppercase
//
//@param  ch - character to convert
//@return the changed character on success
//        the character unchanged on failure
int toupper(int ch);

#endif  // #ifndef _HCLIB_CTYPE_H
