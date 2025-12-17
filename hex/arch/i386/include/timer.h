/*
 * timer.h
 * 	Basic timer functions
 *
 *  Created on: Oct 9, 2011
 *      Author: dragon
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef struct hk_timer_s
{
	int start_day;
	int start_month;
	int start_year;
	int start_hour;
	int start_minute;
	int start_second;
	int start_millisecond;
	int end_day;
	int end_month;
	int end_year;
	int end_hour;
	int end_minute;
	int end_second;
	int end_millisecond;
} hk_timer_t;


hk_timer_t * init_hk_timer();
void destroy_hk_timer(hk_timer_t * timer);

void start_hk_timer(hk_timer_t * timer);
void stop_hk_timer(hk_timer_t * timer);

#endif /* TIMER_H_ */
