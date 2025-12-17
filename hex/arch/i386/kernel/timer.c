/*
 * timer.c
 * 	Basic timer functions
 *
 *  Created on: Oct 9, 2011
 *      Author: dragon
 */

#include <timer.h>
#include <kmm.h>

hk_timer_t * init_hk_timer()
{
	return (hk_timer_t *)kmalloc(sizeof(hk_timer_t));
}

void destroy_hk_timer(hk_timer_t * timer)
{
	if(timer)
	{
		kfree(timer);
		timer = 0;
	}
}
