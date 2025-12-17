/*
 * kdbg.c
 * 	functions that provide kernel debugging control
 *
 *  Created on: Jun 7, 2009
 *      Author: Jeff DiClemente
 */

#include <kdbg.h>
#include <console.h>
#include <portio.h>
#include <serial.h>
#include <common.h>

void set_trace(int bOn)
{
	if(bOn == 0)
		_clear_trace_flag();
	else if(bOn == 1)
		_set_trace_flag();
}

void dbg_break()
{
	_int3();
	_bochs_magic_break();
}

void step()
{
	_int1();
}

void print_dbg_info(isr_context_t * r)
{
	char buf[128];
	memset(buf, 0, 128);

	char opcode[128];
	memset(opcode, 0, 128);

	kprintf("eax = 0x%x ebx = 0x%x ecx = 0x%x edx = 0x%x \nesi = 0x%x edi = 0x%x ebp = 0x%x esp = 0x%x \ncs = 0x%x ds = 0x%x es = 0x%x fs = 0x%x gs = 0x%x ss = 0x%x \neip = 0x%x %s\neflags = 0x%x %s\n",
			r->eax, r->ebx, r->ecx, r->edx,
			r->esi, r->edi, r->ebp, r->esp,
			r->cs, r->ds, r->es, r->fs, r->gs, r->ss,
			r->eip, eip_to_string(r->eip, opcode), r->eflags, eflags_to_string(r->eflags, buf));
	kdbg_log("eax = 0x%x ebx = 0x%x ecx = 0x%x edx = 0x%x \nesi = 0x%x edi = 0x%x ebp = 0x%x esp = 0x%x \ncs = 0x%x ds = 0x%x es = 0x%x fs = 0x%x gs = 0x%x ss = 0x%x \neip = 0x%x %s\neflags = 0x%x %s\n",
				r->eax, r->ebx, r->ecx, r->edx,
				r->esi, r->edi, r->ebp, r->esp,
				r->cs, r->ds, r->es, r->fs, r->gs, r->ss,
				r->eip, eip_to_string(r->eip, opcode), r->eflags, eflags_to_string(r->eflags, buf));

}

void print_stack_trace(isr_context_t * r)
{

}

void pause()
{
	// wait until the user wants to continue (by pressing 'c')
	__asm__ __volatile__ ("hlt");
	/*kprint(CMD_PROMPT);
	char c = readkb();
	while(F10 != c)
		c = readkb();

	// clear the keyboard input buffer, otherwise the next time this function is called, the keyboard's input buffer will still contain 'c'
	outportb(0x60, 0x00);
*/
}

char * eflags_to_string(unsigned int eflags, char * outBuf)
{
	// carry flag CF
	if(CHECK_FLAG(eflags, 0))
		strcat(outBuf, "CF");

	// parity flag PF
	if(CHECK_FLAG(eflags, 2))
		strcat(outBuf, " PF");

	// adjust flag AF
	if(CHECK_FLAG(eflags, 4))
		strcat(outBuf, " AF");

	// zero flag ZF
	if(CHECK_FLAG(eflags, 6))
		strcat(outBuf, " ZF");

	// sign flag SF
	if(CHECK_FLAG(eflags, 7))
		strcat(outBuf, " SF");

	// trap flag TF
	if(CHECK_FLAG(eflags, 8))
		strcat(outBuf, " TF");

	// interrupt enable flag IF
	if(CHECK_FLAG(eflags, 9))
		strcat(outBuf, " IF");

	// direction flag DF
	if(CHECK_FLAG(eflags, 10))
		strcat(outBuf, " DF");

	// overflow flag OF
	if(CHECK_FLAG(eflags, 11))
		strcat(outBuf, " OF");

	// IO privilege level flag IOPL
	if(CHECK_FLAG(eflags, 12) || CHECK_FLAG(eflags, 13))
		strcat(outBuf, " IOPL");

	// nested task flag NT
	if(CHECK_FLAG(eflags, 14))
		strcat(outBuf, " NT");

	// resume flag RF
	if(CHECK_FLAG(eflags, 16))
		strcat(outBuf, " RF");

	// virtual 8086 mode flag VM
	if(CHECK_FLAG(eflags, 17))
		strcat(outBuf, " VM");

	// alignment check AC
	if(CHECK_FLAG(eflags, 18))
		strcat(outBuf, " AC");

	// virtual interrupt flag VIF
	if(CHECK_FLAG(eflags, 19))
		strcat(outBuf, " VIF");

	// virtual interrupt pending flag VIP
	if(CHECK_FLAG(eflags, 20))
		strcat(outBuf, " VIP");

	// Identification flag ID
	if(CHECK_FLAG(eflags, 21))
		strcat(outBuf, " ID");

	return outBuf;
}

char * eip_to_string(unsigned int eip, char * outBuf)
{
	return "";
}

void klog(char * message)
{
	while(*message)
	{	// write to COM 4 port
		write_serial(COM4, *message);
		message++;
	}

	return;
}

void kdbg_log(char * message, ...)
{
	__builtin_va_list va;
	__builtin_va_start(va, message);

	char *str;

	while(*message)
	{
		char buffer[256];
		switch(*message)
		{
			case '%':
				message++;
				switch(*message)
				{
					case 'c':
						write_serial(COM4, __builtin_va_arg(va, int));
						break;
					case 'd':
						itoa(__builtin_va_arg(va ,int), 10, buffer);
						klog(buffer);
						break;
					case 'x':
						uitoa(__builtin_va_arg(va ,unsigned int), 16, buffer);
						klog(buffer);
						break;
					case 'l':
						uitoa(__builtin_va_arg(va ,unsigned int), 10, buffer);
						klog(buffer);
						break;
					case 'f':	/* this is not keeping with the traditional printf format */
						ui64toa(__builtin_va_arg(va ,unsigned long long), 16, buffer);
						klog(buffer);
						break;
					case 's':
						str = (char *)__builtin_va_arg(va, int);
						klog(str);
						break;
				}
				break;
			default:
				write_serial(COM4, *message);
				break;
		}
		message++;
	}
	__builtin_va_end(va);

	return;
}
