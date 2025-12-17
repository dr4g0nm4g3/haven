/*
 * rtc.h - Provides access to the CMOS real-time clock (RTC)
 *
 *  Created on: Jan 21, 2012
 *      Author: dragon
 */

#ifndef RTC_H_
#define RTC_H_

// initialize the RTC by setting the bit in the
//	CMOS so that IRQs will be fired on IRQ 8.
// This function must be called before setting
//	the IRQ handler (rtc_handler) function.
void rtc_init();

// function which is called each time IRQ 8 fires.
void rtc_handler(isr_context_t * r);

#endif /* RTC_H_ */
