/*
 * cmos.c
 * 	functions to read and write from/to the CMOS
 *
 *  Created on: Feb 16, 2009
 *      Author: Jeff DiClemente
 */

#include <system.h>
#include <common.h>		// commonly used functions
#include <kmm.h>		// kmalloc/kfree
#include <kdbg.h>		// debug support
#include <portio.h>		// port IO
#include <console.h>	// display driver

cmos_t * read_cmos()
{
	cmos_t * cmos = (cmos_t *)kmalloc(sizeof(cmos_t));

	if(!cmos)
		return NULL;

	memset((char *)cmos, 0, sizeof(cmos_t));
	unsigned char i = 0;
	unsigned char array[128];

	for(; i < 128; i++)
	{
		//TODO: fix this
		__asm__ __volatile__ ("cli");
		// set the index address into the CMOS
		outportb(0x70, i);
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		// retrieve the data at the index address
		unsigned char data = inportb(0x71);
		__asm__ __volatile__ ("sti");
		kdbg_log("0x%x ", data);
		array[i] = data;
	}
	// copy the contents of the array into the cmos_t data structure
	memcpy((char *)cmos, (const char *)array, sizeof(cmos_t));
	kdbg_log("\n");
	return cmos;
}

void write_cmos(cmos_t * data)
{
	if(data == 0)
		return;

	// TODO: fix me
	unsigned char i = 0;
	for(; i < 128; ++i)
	{
		// turn off interrupts
		__asm__ __volatile__ ("cli");
		// set the index address into the CMOS
		outportb(0x70, i);

		// give the hardware a little time...
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");
		__asm__ __volatile__ ("nop");

		// set the data in the CMOS
		//outportb(0x71, (unsigned char)data[i]);
		// re-enable interrupts
		__asm__ __volatile__ ("sti");

		data++;
	}
}

void display_cmos(cmos_t * cmos)
{
	// TODO: implement
	// for now, just display the time and date

	kdbg_log("seconds: %d\nseconds_alarm: %d\nminutes: %d\nminutes_alarm: %d\nhours: %d\nhours_alarm: %d\nday of week: %d\n \
			day of month: %d\nmonth: %d\nyear: %d\nstatus reg a: %d\nstatus reg b: %d\nstatus reg c: %d\nstatus reg d: %d\n \
			diagnosis reg: %d\nshutdown status: %d\nfloppy: %d\nharddisk: %d\ndevice: %d\nchecksum: %d\ncentury: %d\n",
			cmos->seconds,
			cmos->seconds_alarm,
			cmos->minutes,
			cmos->minutes_alarm,
			cmos->hours,
			cmos->hours_alarm,
			cmos->day_of_week,
			cmos->day_of_month,
			cmos->month,
			cmos->year,
			cmos->a,
			cmos->b,
			cmos->c,
			cmos->d,
			cmos->diagnosis,
			cmos->shutdown,
			cmos->floppy,
			cmos->harddisk,
			cmos->device,
			cmos->checksum,
			cmos->century);
	kprintf("0x%x/0x%x/0x%x 0x%x:0x%x:0x%x\n",
			cmos->day_of_month,
			cmos->month,
			cmos->year,
			cmos->hours,
			cmos->minutes,
			cmos->seconds);
}


