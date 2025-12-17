#ifndef PIT_H_
#define PIT_H_

#include <idt.h>

/* function handler to be installed in an IRQ vector */
void timer_handler(isr_context_t * r);

// initialize the timer frequency for the PIT
void init_timer(unsigned long frequency);

#endif /*PIT_H_*/
