/**
 * HEX - the HAVEN exokernel
 *
 * using the HAVEN native cross compiler:
 *       gcc -o hkernel main.c -Wall -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
 *
 *@author Jeff DiClemente
 *@date   07/27/2008
 */

 /* used for C++ kernel:
  * extern "C" void _main(multiboot_data * mbd, unsigned int magic);
  */

#include <system.h>			// machine specific data/functions
#include <kernel.h>			// kernel specific data/functions
#include <multiboot.h>			// boot manager
#include <kmm.h>				// memory manager
#include "ordered_array.h"
#include <console.h>			// display driver
#include <serial.h>			// serial port support
#include <kdbg.h>				// kernel debugging facilities
#include <rtc.h>				// real-time clock
#include <syscall.h>			// system calls

#include <ut/kmm_unittest.h>	// kernel memory manager unit tests

volatile unsigned long initial_esp;

void log_machine_info(void * mbd)
{
	kdbg_log("*********************\n");
	kdbg_log("multi-boot information:\n");
	kdbg_log("*********************\n");

	multiboot_info_t * mbinfo = (multiboot_info_t *)mbd;
	kdbg_log("flags: 0x%x \n", mbinfo->flags);
	/* Is config_table valid? */
	if (CHECK_FLAG (mbinfo->flags, 8))
	{
		kdbg_log("config_table is at %x\n", mbinfo->config_table);
	}

	/* Is boot_loader_name valid? */
	if (CHECK_FLAG (mbinfo->flags, 9))
	{
		kdbg_log ("boot loader name = %s\n", mbinfo->boot_loader_name);
	}

	/* Is apm_table valid? */
	if (CHECK_FLAG (mbinfo->flags, 10))
	{
		kdbg_log ("APM table at 0x%x\n", mbinfo->apm_table);
		apm_table_t * apm = (apm_table_t *)mbinfo->apm_table;
		kdbg_log("version: 0x%x\ncseg: 0x%x, cseg length: 0x%x\ncseg16: 0x%x, cseg16 length: 0x%x\ndseg: 0x%x, dseg length: 0x%x\n",
				apm->version, apm->cseg, apm->cseg_len, apm->cseg_16, apm->cseg_16_len, apm->dseg, apm->dseg_len);
	}

	/* Is graphics table valid? */
	if (CHECK_FLAG (mbinfo->flags, 11))
	{
		kdbg_log ("VBE ctrl_info at 0x%x, mode_info at 0x%x, mode=0x%x\n"
			  "    interface seg = 0x%x, off = 0x%x, len = 0x%x\n",
			  mbinfo->vbe_control_info, mbinfo->vbe_mode_info,
			  mbinfo->vbe_mode,
			  mbinfo->vbe_interface_seg, mbinfo->vbe_interface_off,
			  mbinfo->vbe_interface_len
			  );
	}

	detect_memory(mbd);

	kdbg_log("*********************\n");
	kdbg_log("cpuid information:\n");
	kdbg_log("*********************\n");
	detect_cpu();

	detect_devices(mbd);

	kdbg_log("*********************\n");
	kdbg_log("CMOS information:\n");
	kdbg_log("*********************\n");
	cmos_t * cmos = read_cmos();
	if(!cmos)
		kdbg_log("Reading the cmos returned a NULL pointer to the cmos_t data structure");
	else
	{
		display_cmos(cmos);
		kfree(cmos);
	}
}

void _main(void * mbd, unsigned long magic, unsigned long initial_stack_ptr)
{
	initial_esp = initial_stack_ptr;

	/* clear the screen */
	cls();

	hex_init();

	/* enable interrupts */
	__asm__ __volatile__ ("sti");

	/* print a message */
	kprint("we're in the kernel bitches!\n");

	kdbg_log("initial esp = 0x%x\n", initial_esp);

	// set up kernel heap
	kmm_init();

	// unit test the kernel memory manager
	// TODO: only compile the unit test code
	//	into the build for debug or special "test"
	//	build configurations of the kernel
	//test_kmm();

	log_machine_info(mbd);

	kprintf("Issuing a system call interrupt from the kernel...\n");
	__asm__ __volatile__ ("int $0x80");

	/*
	 * proof of concept;
	 * test calling the kernel from user mode
	 * and then return to kernel mode.
	 */
	switch_to_user_mode();
	/*
	 * end - proof of concept
	 */

	kprint(CMD_PROMPT);

	for(;;)
		__asm__ __volatile__ ("hlt");

}

/**
  *		initializations for HEX
  *
  * 	includes:
  * 		installing the GDT and IDT
  * 		reprogramming the PIC
  * 		installing IRQ handlers
  * 		initializing data structures used by HEX
  */
void hex_init()
{
	gdt_install();
	idt_install();
	irq_install();
	syscall_initialize();
	// initialize timer to 50Mhz
	init_timer(50);

	if(has_apic())
		enable_apic();

	// initialize COM serial ports
	init_serial(COM1);
	init_serial(COM2);
	init_serial(COM3);
	init_serial(COM4);

	// must initialize the RTC before setting the IRQ handler for it.
	//rtc_init();

	install_irq_handler(0, &timer_handler);
	install_irq_handler(1, &kb_handler);
	//install_irq_handler(8, &rtc_handler);

}

