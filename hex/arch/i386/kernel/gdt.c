/**
 * gdt.c - Global Descriptor Table implementation
 *
 * NOTE: the first entry of a GDT needs to be NULL
 *
 * @author Jeff DiClemente
 * @date 09/28/2008
 */

#include <system.h>
#include <gdt.h>

/* set an entry in the GDT */
void set_gdt_gate(int entry_num, unsigned long base_address, unsigned long limit, unsigned char access, unsigned char flags)
{
	gdt[entry_num].limit = (limit & 0xFFFF);
	gdt[entry_num].base_address_low = (base_address & 0xFFFF);
	gdt[entry_num].base_address_middle = (base_address >> 16) & 0xFF;
	gdt[entry_num].base_address_high = (base_address >> 24) & 0xFF;
	gdt[entry_num].granularity = ((limit >> 16) & 0x0F);
	gdt[entry_num].granularity |= (flags & 0xF0);
	gdt[entry_num].access = access;
}

/* replace the current GDT with the one created here */
void gdt_install()
{
	pgdt.limit = (sizeof(gdt_entry) * 6) - 1;
	pgdt.address = (int)&gdt;

	/* set NULL entry */
	set_gdt_gate(0, 0, 0, 0, 0);

	/* set ring 0 code segment descriptor */
	// access byte = (SEG_CODE_EXRD | SEG_PRESENT | SEG_CODE_DATA_TYPE)
	// flags nibble = (SEG_FLAG_SIZE | SEG_FLAG_GRAN )
	set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	/* set ring 0 data segment descriptor */
	// access byte = (SEG_DATA_RDWR | SEG_PRESENT | SEG_CODE_DATA_TYPE)
	// flags nibble = (SEG_FLAG_SIZE | SEG_FLAG_GRAN )
	set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	/* set a ring 3 code segment descriptor */
	// access byte = (SEG_CODE_EXRD | SEG_PRESENT | SEG_CODE_DATA_TYPE | SEG_PRIV_RING3)
	// flags nibble = (SEG_FLAG_SIZE | SEG_FLAG_GRAN )
	set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

	/* set a ring 3 data segment descriptor */
	// access byte = (SEG_DATA_RDWR | SEG_PRESENT | SEG_CODE_DATA_TYPE | SEG_PRIV_RING3)
	// flags nibble = (SEG_FLAG_SIZE | SEG_FLAG_GRAN )
	set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	/* set a TSS descriptor for ring 3
	 * a TSS descriptor will allow switching back to ring 0
	 * from a task in ring 3
	 *
	 * Normal practice when implementing software task switching
	 * is just to have one TSS, and update the ESP0 field of it
	 * whenever a task switch takes place - this is the minimum
	 * work neccessary to allow system calls to work properly.
	 */
	init_tss(&ring3_tss);
	unsigned long limit = (unsigned long)&ring3_tss + sizeof(tss_t);
	// access byte = (SEG_SYS_32BIT_TSSA | SEG_PRESENT | SEG_PRIV_RING3)
	// flags nibble = 0
	set_gdt_gate(5, (unsigned long)&ring3_tss, limit, 0xE9, 0);

	_gdt_flush();
	/* load segment selector (GDT entry of the TSS) into the task register */
	load_task_register(0x2B);
}
