/**
 * irq.c - interrupt request handlers for IRQ 0 - IRQ 15 
 * 
 * @author Jeff DiClemente
 * @date 08/27/2008
 */

#include <console.h>
#include <idt.h>
#include <pic.h>

extern void _irq0();	// Programmable Interrupt Timer
extern void _irq1();	// Keyboard Interrupt
extern void _irq2();	// cascade; not used
extern void _irq3();	// COM2
extern void _irq4();	// COM1
extern void _irq5();	// ???
extern void _irq6();	// Floppy Disk
extern void _irq7();	// "spurious" interrupt
extern void _irq8();	// CMOS real-time clock
extern void _irq9();	// ???
extern void _irq10();	// ???
extern void _irq11();	// ???
extern void _irq12();	// ???
extern void _irq13();	// ???
extern void _irq14();	// Primary ATA hard disk
extern void _irq15();	// Secondary ATA hard disk

/* hold function pointers to IRQ handler routines */
void * irq_funcptrs[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* remap IRQs 0 - 15 to ISR 32 - 47 */
void irq_remap()
{
	remap_pic(0x20, 0x28);
}

/* set function pointers for IRQs */
void irq_install()
{
	/* remap IRQs 0-15 from 8 - 15 and 112 - 119 to 32 - 47 in the IDT */
	irq_remap();
	
	/* set the appropriate entries in the IDT */
	set_idt_gate(32, (unsigned long)&_irq0, 0x08, 0x8E);
	set_idt_gate(33, (unsigned long)&_irq1, 0x08, 0x8E);
	set_idt_gate(34, (unsigned long)&_irq2, 0x08, 0x8E);
	set_idt_gate(35, (unsigned long)&_irq3, 0x08, 0x8E);
	set_idt_gate(36, (unsigned long)&_irq4, 0x08, 0x8E);
	set_idt_gate(37, (unsigned long)&_irq5, 0x08, 0x8E);
	set_idt_gate(38, (unsigned long)&_irq6, 0x08, 0x8E);
	set_idt_gate(39, (unsigned long)&_irq7, 0x08, 0x8E);
	set_idt_gate(40, (unsigned long)&_irq8, 0x08, 0x8E);
	set_idt_gate(41, (unsigned long)&_irq9, 0x08, 0x8E);
	set_idt_gate(42, (unsigned long)&_irq10, 0x08, 0x8E);
	set_idt_gate(43, (unsigned long)&_irq11, 0x08, 0x8E);
	set_idt_gate(44, (unsigned long)&_irq12, 0x08, 0x8E);
	set_idt_gate(45, (unsigned long)&_irq13, 0x08, 0x8E);
	set_idt_gate(46, (unsigned long)&_irq14, 0x08, 0x8E);
	set_idt_gate(47, (unsigned long)&_irq15, 0x08, 0x8E);
}

void install_irq_handler(int irq, void (*handler)(isr_context_t * r))
{
	irq_funcptrs[irq] = handler;
	kprintf("IRQ %d installed, function pointer = %x\n", irq, handler);
}

void uninstall_irq_handler(int irq)
{
	irq_funcptrs[irq] = 0;
	kprintf("IRQ %d uninstalled\n", irq);
}

/*  IRQ handler for all IRQs which, in turn, calls the appropriate function pointer */
void irq_handler(isr_context_t * r)
{	
	void (*handler)(isr_context_t * r);
	handler = irq_funcptrs[r->int_no - 32];
	
	if(handler)
		handler(r);
	
	/* send EOI (end of interrupt) */
	send_eoi(r->int_no);
}
