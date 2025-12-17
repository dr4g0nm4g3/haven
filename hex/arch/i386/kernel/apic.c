/*
 * apic.c
 *
 *  Created on: Feb 24, 2014
 *      Author: dragon
 */

#include <hktypes.h>
#include <apic.h>

/* APIC MSR Base is at 0x1b */
#define IA32_APIC_BASE_MSR 0x1B
/* APIC global enable/disable bit - APIC_BASE[11] */
#define IA32_APIC_BASE_MSR_ENABLE 0x800

void get_msr(uint32_t msr, uint32_t *lo, uint32_t *hi)
{
   __asm__ __volatile__("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}

void set_msr(uint32_t msr, uint32_t lo, uint32_t hi)
{
   __asm__ __volatile__("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}

void enable_apic(void)
{
#if defined (HEX_ENABLE_APIC_SUPPORT)
	uint32_t low, high;
	get_msr(IA32_APIC_BASE_MSR, &low, &high);

	/*
	 * APIC Base MSR (64-bit)
	 * bits 63:36 are Reserved
	 * bits 35:12 is the APIC Base
	 * bit 11 is the Global enable flag
	 * bits 10:9 are Reserved
	 * bit 8 is the BSP (Bootstrap Processor) flag
	 * bits 7:0 are Reserved
	 */

	/*
	 * preserve the last 19 bits, plus bit 8 (BSP flag) from the low
	 * 32-bits of the MSR and the first 4 bits from the high 32-bits
	 * to form the apic's 24-bit base address.
	 */
	uint32_t apic = (low & 0xfffff100) | ((high & 0x0f) << 31);

	low = (apic & 0xfffff100) | IA32_APIC_BASE_MSR_ENABLE;
	high = (apic >> 31) & 0x0f;
	set_msr(IA32_APIC_BASE_MSR, low, high);
#endif
}
