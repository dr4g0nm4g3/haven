#ifndef IDT_H_
#define IDT_H_

/* data structures */

/* defines the state of the machine registers after an ISR */
typedef struct isr_context_s
{
	unsigned int gs, fs, es, ds;								/* pushed last by the common ISR stub function */
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;		/* pushed by the 'pushad' opcode */
	unsigned int int_no, ec;									/* pushed by our _isr* functions */
	unsigned int eip, cs, eflags, useresp, ss;					/* pushed by the processor automatically */
} isr_context_t;

/*
 * offset_low	bits 0 - 15 - Lower part of the interrupt function's offset address (0 - 15)
 * selector		bits 16 - 31 - Selector of the interrupt function (to make sense - the kernel's selector).
 * 								The selector's descriptor's DPL field has to be 0.
 * 								The selector is a 16 bit value and must point to a valid selector in your GDT.
 * zero			bits 32 - 39 - unused, must be 0
 * type_attr 	bits 40 - 48 - A byte which holds multiple pieces of information. The bit field is specified as:
 *   7                           0
 *	+---+---+---+---+---+---+---+---+
 *	| P |  DPL  | S |    GateType   |
 *	+---+---+---+---+---+---+---+---+
 *
 * 	P	 47	 	Present	 					Can be set to 0 for unused interrupts or for Paging.
 *	DPL	 45,46	Descriptor Privilege Level	Gate call protection. Specifies which privilege Level the calling Descriptor minimum should have.
 *											So hardware and CPU interrupts can be protected from being called out of userspace.
 *	S	 44	 	Storage Segment				set to 0 for interrupt gates.
 *	Type 40..43	Gate Type 	 				Possible IDT gate types:
 *											binary	 hex	 decimal 	description
 *											--------------------------------------------------
 *											0b0101	 0x5	 5	 		80386 32 bit Task gate
 *											0b0110	 0x6	 6	 		80286 16-bit interrupt gate
 *											0b0111	 0x7	 7	 		80286 16-bit trap gate
 *											0b1110	 0xE	 14	 		80386 32-bit interrupt gate
 *											0b1111	 0xF	 15	 		80386 32-bit trap gate
 *
 * offset_high	bits 48 - 63 - Higher part of the offset (16 - 31)
 */
typedef struct idt_entry_s
{
	unsigned short offset_low;
	unsigned short selector;				/* code segment selector in GDT or LDT */
	unsigned char zero;					/* always zero */
	unsigned char type_attr;			/* gate type and attributes */
	unsigned short offset_high;
}__attribute__((packed))idt_entry;

typedef struct idt_ptr_s
{
	unsigned short limit;
	unsigned int address;
}__attribute__((packed))idt_ptr;

idt_entry idt[256];
idt_ptr pidt;

/* function prototypes */
void irq_remap();
void irq_install();
void install_irq_handler(int irq, void (*handler)(isr_context_t * r));
void uninstall_irq_handler(int irq);
void irq_handler(isr_context_t * r);

void idt_install();

/* implemented elsewhere */
extern void _idt_load();

void set_idt_gate(unsigned char num, unsigned long func_ptr, unsigned short selector, unsigned char access_flags);
void isr_setup();
void fault_handler(isr_context_t * r);

#endif /*IDT_H_*/
