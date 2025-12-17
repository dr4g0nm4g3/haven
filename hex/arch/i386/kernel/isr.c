/**
 * isr.c - interrupt service requests for ISR 0 - ISR 31
 *
 * @author Jeff DiClemente
 * @date 08/27/2008
 */

#include <console.h>
#include <portio.h>
#include <idt.h>
#include <kdbg.h>

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

/* exception strings */
char * exception_msgs[20] = {
		"Divide by Zero",
		"Debug Exception",
		"Non Maskable Interrupt Exception",
		"Breakpoint Exception",
		"Into Detected Overflow Exception",
		"Out of Bounds Exception",
		"Invalid Opcode Exception",
		"No Coprocessor Exception",
		"Double Fault Exception",
		"Coprocessor Segment Overrun Exception",
		"Bad TSS Exception",
		"Segment Not Present Exception",
		"Stack Fault Exception",
		"General Protection Fault Exception",
		"Page Fault Exception",
		"Unknown Interrupt Exception",
		"Coprocessor Fault Exception",
		"Alignment Check Exception (486+)",
		"Machine Check Exception (Pentium/586+)",
		"Reserved"	/* ISRs 19 - 31 */
};

/* setup all ISRs */
void isr_setup()
{
	set_idt_gate(0, (unsigned long)&_isr0, 0x08, 0x8E);
	set_idt_gate(1, (unsigned long)&_isr1, 0x08, 0x8E);
	set_idt_gate(2, (unsigned long)&_isr2, 0x08, 0x8E);
	set_idt_gate(3, (unsigned long)&_isr3, 0x08, 0x8E);
	set_idt_gate(4, (unsigned long)&_isr4, 0x08, 0x8E);
	set_idt_gate(5, (unsigned long)&_isr5, 0x08, 0x8E);
	set_idt_gate(6, (unsigned long)&_isr6, 0x08, 0x8E);
	set_idt_gate(7, (unsigned long)&_isr7, 0x08, 0x8E);
	set_idt_gate(8, (unsigned long)&_isr8, 0x08, 0x8E);
	set_idt_gate(9, (unsigned long)&_isr9, 0x08, 0x8E);
	set_idt_gate(10, (unsigned long)&_isr10, 0x08, 0x8E);
	set_idt_gate(11, (unsigned long)&_isr11, 0x08, 0x8E);
	set_idt_gate(12, (unsigned long)&_isr12, 0x08, 0x8E);
	set_idt_gate(13, (unsigned long)&_isr13, 0x08, 0x8E);
	set_idt_gate(14, (unsigned long)&_isr14, 0x08, 0x8E);
	set_idt_gate(15, (unsigned long)&_isr15, 0x08, 0x8E);
	set_idt_gate(16, (unsigned long)&_isr16, 0x08, 0x8E);
	set_idt_gate(17, (unsigned long)&_isr17, 0x08, 0x8E);
	set_idt_gate(18, (unsigned long)&_isr18, 0x08, 0x8E);
	set_idt_gate(19, (unsigned long)&_isr19, 0x08, 0x8E);
	set_idt_gate(20, (unsigned long)&_isr20, 0x08, 0x8E);
	set_idt_gate(21, (unsigned long)&_isr21, 0x08, 0x8E);
	set_idt_gate(22, (unsigned long)&_isr22, 0x08, 0x8E);
	set_idt_gate(23, (unsigned long)&_isr23, 0x08, 0x8E);
	set_idt_gate(24, (unsigned long)&_isr24, 0x08, 0x8E);
	set_idt_gate(25, (unsigned long)&_isr25, 0x08, 0x8E);
	set_idt_gate(26, (unsigned long)&_isr26, 0x08, 0x8E);
	set_idt_gate(27, (unsigned long)&_isr27, 0x08, 0x8E);
	set_idt_gate(28, (unsigned long)&_isr28, 0x08, 0x8E);
	set_idt_gate(29, (unsigned long)&_isr29, 0x08, 0x8E);
	set_idt_gate(30, (unsigned long)&_isr30, 0x08, 0x8E);
	set_idt_gate(31, (unsigned long)&_isr31, 0x08, 0x8E);

}

/*
 * default fault handler for ISRs 0 - 31
 * 	NOTE: for now, simply print the exception name when it occurs
 */
void fault_handler(isr_context_t * r)
{
	if(r->int_no >= 19)
	{
		kprintf("%s (%d) ec: %d\n", exception_msgs[19], r->int_no, r->ec);		// print 'Reserved'
	}
	else if(r->int_no == 1 || r->int_no == 3)
	{
		kprintf("%s (%d) ec: %d\n", exception_msgs[r->int_no], r->int_no, r->ec);
		print_dbg_info(r);
	}
	else
	{
		if(r->int_no == 13)
		{
			_bochs_magic_break();
			kprintf("%s (%d) ec: %d\nInstruction 0x%x\n", exception_msgs[r->int_no], r->int_no, r->ec, r->eip);	//print exception string
			//__asm__ __volatile__ ("hlt");
		}
		else
		{
			kprintf("%s (%d) ec: %d\n", exception_msgs[r->int_no], r->int_no, r->ec);	//print exception string
			//__asm__ __volatile__ ("hlt");
		}
	}
}
