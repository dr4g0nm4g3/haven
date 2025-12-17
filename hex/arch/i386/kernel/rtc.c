/*
 * rtc.c
 *
 *  Created on: Jan 21, 2012
 *      Author: dragon
 */

#include <system.h>
#include <portio.h>		// port IO
#include <kdbg.h>		// debugging
#include <rtc.h>

void rtc_init()
{
	__asm("cli");
	outportb(0x70, 0xb);					// set the index into the CMOS to register 'b'
	unsigned char current = inportb(0x71);	// save the current value in register 'b'
	outportb(0x70, 0xb);					// set the index again since a read resets the index to register 'd'
	outportb(0x71, current | 0x40);			// keep the existing value and turn on bit 6 to enable RTC interrupts.
	__asm("sti");
}

void rtc_handler(isr_context_t * r)
{
	// according to http://wiki.osdev.org/RTC, if register C is
	//	not read, then this interrupt will not happen again.
	// So, read register C whenever IRQ 8 fires and just discard
	//	the value.
	outportb(0x70, 0x0c);
	inportb(0x71);
	kdbg_log("IRQ 8 fired");
}
