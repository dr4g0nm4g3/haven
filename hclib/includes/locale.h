/*
 * locale.h - header for locale information
 *
 * date: 08/18/2007
 * author: Jeff DiClemente
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

// TODO: implementation

#ifndef _HCLIB_LOCALE_H
#define _HCLIB_LOCALE_H _HCLIB_LOCALE_H

#ifndef _HCLIB_AUX_H
#define _HCLIB_AUX_H _HCLIB_AUX_H
#include <_HCLIB_aux.h>
#endif

#ifndef _HCLIB_INT_H
#define _HCLIB_INT_H
#include <_HCLIB_int.h>
#endif

#ifndef _HCLIB_CONFIG_H
#define _HCLIB_CONFIG_H
#include <_HCLIB_config.h>
#endif

/* value of a NULL pointer constant */
#ifndef _HCLIB_NULL_DEFINED
#define _HCLIB_NULL_DEFINED _HCLIB_NULL_DEFINED
#define NULL _HCLIB_NULL
#endif

#define LC_ALL 		0	/* category argument for all categories */
#define LC_NUMERIC 	1	/* category for numeric formatting information */
#define LC_MONETARY 	2	/* category for monetary formatting information */
#define LC_COLLATE 	3	/* category for information affecting collating functions */
#define LC_CTYPE 		4	/* category for affecting characters class test functions */
#define LC_TIME 		5	/* category for information affecting time conversion functions */

struct lconv
{	/* describes formatting of monetary and other numeric values */
	char * decimal_point;		/* decimal point for non-monetary values */
	char * grouping;			/* sizes of digit groups for non-monetary values */
	char * thousands_sep;		/* seperator of digit groups for non-monetary values (left of "decimal point") */
	char * currency_symbol;	/* currency symbol */
	char * int_curr_symbol;	/* international currency symbol */
	char * mon_decimal_point;	/* decimal point for monetary values */
	char * mon_grouping;		/* sizes of digit groups for monetary values */
	char * mon_thousands_sep;	/* seperator for digit groups for monetary values (left of "decimal point") */
	char * negative_sign;		/* negative sign for monetary values */
	char * positive_sign;		/* positive sign for monetary values */
	char frac_digits;			/* # of digits to be displayed to right of "decimal point" for monetary values */
	char int_frac_digits;		/* # of digits to be displayed to right of "decimal point" for international monetary values */
	char n_cs_precedes;		/* whether currency symbol precedes (1) or follows (0) negative monetary values */
	char n_sep_by_space;		/* whether currency symbol is (1) or is not (0) seperated by space from negative monetary values */
	char n_sign_posn;			/* format for negative monetary values
								 * 0 - parentheses surrond quantity and currency symbol
								 * 1 - sign precedes quantity and currency symbol
								 * 2 - sign follows quantity and currency symbol
								 * 3 - sign immediately precedes currency symbol
								 * 4 - sign immediately follows currency symbol
								 */
	char p_cs_precedes;		/* whether currency symbol precedes (1) or follows (0) positive monetary values */
	char p_sep_by_space;		/* whether currency symbol is (1) or is not (0) seperated by space from positive monetary values */
	char p_sign_posn;			/* format for positive monetary values, with values as for n_sign_posn */
};

/* returns pointer to formatting information for current locale */
struct lconv * localeconv(void);

/*
	Sets or reads location dependent information.

	category can be one of the following:
	LC_ALL	Set everything.
	LC_COLLATE	Affects strcoll and strxfrm functions.
	LC_CTYPE	Affects all character functions.
	LC_MONETARY	Affects the monetary information provided by localeconv function.
	LC_NUMERIC	Affects decimal-point formatting and the information provided by localeconv function.
	LC_TIME	Affects the strftime function.

	A value of "C" for locale sets the locale to the normal C translation environment settings (default).
	A null value ("") sets the native environment settings.
	A null pointer (NULL) causes setlocale to return a pointer to the string associated with this category for the current settings (no changes occur).
	All other values are implementation-specific.

	After a successful set, setlocale returns a pointer to a string which represents the previous location setting.
	On failure it returns NULL.
 */
char * setlocale(int category, const char * locale);

#endif /* _HCLIB_LOCALE_H */
