/*
 * common.c
 *   helper functions that will be replaced eventually
 *
 *  Created on: Mar 15, 2009
 *      Author: dragon
 */

#include <common.h>
#include <kdbg.h>

int kabs(int n)
{
	if(n>=0)
		return n;
	else
		return (n*(-1));
}

char hexdigit(int n)
{
	char x;
	switch(n)
	{
		case 10:
			x='A';
			break;
		case 11:
			x='B';
			break;
		case 12:
			x='C';
			break;
		case 13:
			x='D';
			break;
		case 14:
			x='E';
			break;
		case 15:
			x='F';
			break;
		default:
			x=n+0x30;
			break;
	}
	return x;
}

void itoa(int num, unsigned int base, char *buffer)
{
	unsigned int r=0;
	int i=0;
	char tmp[32];
	if(num<0)
		*buffer++='-';
	num=kabs(num);
	if(num < base)
	{
		*buffer++ = hexdigit(num);
		*buffer='\0';
		return;
	}
	if(num >= base)
		while(num)
		{
			r=num % base;
			num /= base;
			tmp[i++] = hexdigit(r);
		}
	i--;
	for( ; i>=0 ; i--)
		*buffer++=tmp[i];
	*buffer='\0';
}

void uitoa(unsigned int num, unsigned int base, char *buffer)
{
	unsigned int r=0;
	int i=0;
	char tmp[32];
	if(num < base)
	{
		*buffer++ = hexdigit(num);
		*buffer='\0';
		return;
	}
	if(num >= base)
		while(num)
		{
			r=num % base;
			num /= base;
			tmp[i++] = hexdigit(r);
		}
	i--;
	for( ; i>=0 ; i--)
		*buffer++=tmp[i];
	*buffer='\0';
}

void ui64toa(unsigned int num, unsigned int base, char *buffer)
{
	unsigned int r=0;
	int i=0;
	char tmp[64];
	if(num < base)
	{
		*buffer++ = hexdigit(num);
		*buffer='\0';
		return;
	}
	if(num >= base)
		while(num)
		{
			r=num % base;
			num /= base;
			tmp[i++] = hexdigit(r);
		}
	i--;
	for( ; i>=0 ; i--)
		*buffer++=tmp[i];
	*buffer='\0';
}

int strlen(const char * str)
{
	int len = 0;
	while(*str)
	{
		len++;
		str++;
	}
	return len;
}

void memcpy(char * dest, const char * src, unsigned long len)
{
    const char * sp = (const char *)src;
    char * dp = (char *)dest;
    for(; len != 0; len--)
    	*dp++ = *sp++;
}

/*void memset(char * dest, char val, unsigned long len)
{
    char * temp = (char *)dest;
    for ( ; len != 0; len--)
    	*temp++ = val;
}*/

void memset( void * s, int c, unsigned long n )
{
    unsigned char * p = (unsigned char *) s;
    while ( n-- )
    {
        *p++ = (unsigned char) c;
    }
}

int strcmp(const char * str1, const char * str2)
{
	while ( ( *str1 ) && ( *str1 == *str2 ) )
	{
		++str1;
		++str2;
	}
	return ( *str1 - *str2 );
}

char * strcpy(char * dest, const char * src)
{
    do
    {
      *dest++ = *src++;
    }
    while (*src != 0);
    return dest;
}

char * strncpy( char * s1, const char * s2, unsigned long n )
{
    char * rc = s1;
    while ( ( n > 0 ) && ( *s1++ = *s2++ ) )
    {
        /* Cannot do "n--" in the conditional as size_t is unsigned and we have
        to check it again for >0 in the next loop.
        */
        --n;
    }
    /* FIXME: This works correctly, but somehow the handling of n is ugly as
       hell.
    */
    if ( n > 0 )
    {
        while ( --n )
        {
            *s1++ = '\0';
        }
    }
    return rc;
}

char * strcat(char * dest, const char * src)
{
    char * rc = dest;
	if ( *dest )
	{
		while ( *++dest );
	}
	while ( (*dest++ = *src++) );
	return rc;
}

char * strncat( char * s1, const char * s2, unsigned long n )
{
    char * rc = s1;
    while ( *s1 )
    {
        ++s1;
    }
    while ( n && ( *s1++ = *s2++ ) )
    {
        --n;
    }
    if ( n == 0 )
    {
        *s1 = '\0';
    }
    return rc;
}
