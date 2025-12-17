/*
 * common.h
 *
 *  Created on: Mar 15, 2009
 *      Author: dragon
 */

#ifndef COMMON_H_
#define COMMON_H_

#define sizeofarray(x) sizeof(x)/sizeof(x[0])

void itoa(int num, unsigned int base, char *buffer);
void uitoa(unsigned int num, unsigned int base, char *buffer);
void ui64toa(unsigned int num, unsigned int base, char *buffer);
int strlen(const char * str);
char hexdigit(int n);
int kabs(int n);

// Copy len bytes from src to dest.
void memcpy(char * dest, const char * src, unsigned long len);
// Write len copies of val into dest.
//void memset(char * dest, char val, unsigned long len);
void memset(void * s, int c, unsigned long n );
// Compare two strings. Should return -1 if
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(const char * str1, const char * str2);
// Copy the NULL-terminated string src into dest, and
// return dest.
char * strcpy(char * dest, const char * src);
char * strncpy( char * s1, const char * s2, unsigned long n );
// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char * strcat(char * dest, const char * src);
char * strncat( char * s1, const char * s2, unsigned long n );

#endif /* COMMON_H_ */
