/**
 * pic.c - implement functions for the 8259A programmable interrupt controller (PIC)
 * 
 * @author Jeff DiClemente
 * @date 10/03/2008
 */

#include <pic.h>
#include <portio.h>

void send_eoi(unsigned char irq)
{
	if(irq >= 40)
		outportb(PIC2_COMMAND, PIC_EOI);
		
	outportb(PIC1_COMMAND, PIC_EOI);
}

void remap_pic(unsigned int master_offset, unsigned int slave_offset)
{
	unsigned char irq_mask = inportb(PIC1_DATA);
	unsigned char irq_slave_mask = inportb(PIC2_DATA);
	
	/* send the initialization commands */
	outportb(PIC1_COMMAND, 0x11);
	outportb(PIC2_COMMAND, 0x11);
	
	/* set the master and slave interrupt vectors */
	outportb(PIC1_DATA, master_offset);
	outportb(PIC2_DATA, slave_offset);
	
	/* set which IRQs the master and slave are connected by */
	outportb(PIC1_DATA, 0x04);
	outportb(PIC2_DATA, 0x02);
	
	/* set 80x86 mode */
	outportb(PIC1_DATA, 0x01);
	outportb(PIC2_DATA, 0x01);
	
	/* clear our IRQ masks */
	outportb(PIC1_DATA, 0x0);
	outportb(PIC2_DATA, 0x0);
	
	// restore old IRQ masks
	outportb(PIC1_DATA, irq_mask);
	outportb(PIC2_DATA, irq_slave_mask);
}
