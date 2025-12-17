/*
 * time.h - header for time and date functions
 *
 * date: 08/18/2007
 * author: Jeff DiClemente
 *
 * This library supports ISO/IEC 9899:1990, 9899/AMD1:1995, and 9899:1999
 *
 * Copyright (C) 2007, Gran Sasso LLC
 */

// TODO: implementation

#ifndef _HCLIB_TIME_H
#define _HCLIB_TIME_H _HCLIB_TIME_H

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

//TODO: define CLOCKS_PER_SEC in terms of clock_t
#define CLOCKS_PER_SEC 0L

struct tm
{
	int tm_sec;	/* seconds after the minute */
	int tm_min;	/* minutes after the hour */
	int tm_hour;	/* hours since midnight */
	int tm_mday;	/* day of the month */
	int tm_mon;	/* months since January */
	int tm_year;	/* years since 1900 */
	int tm_wday;	/* days since Sunday */
	int tm_yday;	/* days since January 1 */
	int tm_isdst;	/* daylight savings time flag. positive if DST is in effect; zero if not; negative if information unknown */
};

/* an arithmetic type elapsed processor representing time */
typedef long clock_t;

/* an arithmetic type representing calendar time */
typedef long time_t;

typedef _HCLIB_size_t size_t;

/* returns elapsed processor time used by the program or -1 if not available */
clock_t clock(void);

/* returns calendar time or -1 if not available. if tp is non-NULL, return value is also assigned to *tp */
time_t time(time_t * tp);

/* returns difference in seconds between time2 and time1 */
double difftime(time_t time1, time_t time2);

/* adjusts the fields of *tp to faill within normal ranges. returns the corresponding calendar time, or -1 if not represented */
time_t mktime(struct tm * tp);

/* returns the given time as a string of form: Sun Jan 2 14:23:01 1997\n\0 */
char * asctime(const struct tm * tp);

/* returns string equivalent to calendar time tp converted to local time. equivalent to: asctime(localtime(tp)) */
char * ctime(const time_t * tp);

/* returns calendar time *tp converted to coordinated universal time, or NULL if not available */
struct tm * gmtime(const time_t * tp);

/* returns calendar time *tp converted to local time */
struct tm * localtime(const time_t * tp);

/* formats *tp into s according to fmt. Places no more than smax characters into s, and returns # of characters produced
 * (excluding terminating NULL), or 0 if greater than smax.
 * Formatting conversions (%c) are:
 * A - name of weekday
 * a - abbreviated name of weekday
 * B - name of month
 * b - abbreviated name of month
 * c - local date and time representation
 * d - day of month [01-31]
 * H - hour (24 hour clock) [00-23]
 * I - hour (12 hour clock) [01-12]
 * j - day of year [001-366]
 * M - minute [00-59]
 * m - month [01-12]
 * p - local equivalent of "AM" or "PM"
 * S - second [00-61]
 * U - week # of year (Sunday as 1st day of week) [00-53]
 * W - week # of year (Monday as 1st day of week) [00-53]
 * w - weekday (Sunday as 0) [0-6]
 * X - local time representation
 * x - local date representation
 * Y - year with century
 * y - year without century [00-99]
 * Z - name (if any) of time zone
 * % - %
 */
 size_t strftime(char * s, size_t smax, const char * fmt, const struct tm * tp);


 #endif /* _HCLIB_TIME_H */

