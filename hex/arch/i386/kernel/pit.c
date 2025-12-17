/**
  *		pit.c - implementation of the PIT, programmable interrupt timer
  *
  * @author Jeff DiClemente
  * @date 11/01/2008
  */

#include <pit.h>
#include <portio.h>
#include <timer.h>
#include <kdbg.h>

volatile int timer_ticks = 0;
// keep track of how many cycles have passed. Can be used to implement a crude
//	set of timer functions.
volatile long long timer_count = 0;
// the amount of time given to each running process
static volatile int time_slice = 2000;

void timer_handler(isr_context_t * r)
{
	timer_ticks++;
	if(timer_ticks >= time_slice)
	{
		timer_ticks = 0;// time slice is up, switch threads
	}

}

void init_timer(unsigned long frequency)
{
	// The value we send to the PIT is the value to divide it's input clock
	// (1193180 Hz) by, to get our required frequency. Important to note is
	// that the divisor must be small enough to fit into 16-bits.
	unsigned long divisor = 1193180 / frequency;

	// Send the command byte.
	outportb(0x43, 0x36);

	// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	unsigned char l = (unsigned char) (divisor & 0xFF);
	unsigned char h = (unsigned char) ( (divisor >> 8) & 0xFF );

	// Send the frequency divisor.
	outportb(0x40, l);
	outportb(0x40, h);
}
