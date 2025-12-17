/**
 * idt.c - implementation of the Interrupt descriptor table
 * 
 * @author Jeff DiClemente
 * @date 09/30/2008
 */

#include <idt.h>

/* initialize data structure and setup all ISRs */
void idt_install()
{
	pidt.limit = (sizeof(idt_entry) * 256) - 1;
	pidt.address = (int)&idt;
	
	_idt_load();
	
	isr_setup();
}

/* set a specific an entry in the IDT */
void set_idt_gate(unsigned char num, unsigned long func_ptr, unsigned short selector, unsigned char access_flags)
{
	idt[num].offset_low = func_ptr & 0xFFFF;
	idt[num].selector = selector;
	idt[num].zero = 0;
	idt[num].type_attr = access_flags;
	idt[num].offset_high = (func_ptr >> 16) & 0xFFFF;
}
