#include <system.h>
#include <kdbg.h>

#define cpuid(in, a, b, c, d) __asm__ __volatile__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

/* Simply call this function detect_cpu(); */

/*
 * TODO: use this function to later set environment variables to determine
 *  the CPU features available to the kernel
 **/
int detect_cpu(void) { /* or main() if your trying to port this as an independant application */
	unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch(ebx) {
		case 0x756e6547: /* Intel Magic Code */
		do_intel();
		break;
		case 0x68747541: /* AMD Magic Code */
		do_amd();
		break;
		default:
			kdbg_log("Unknown x86 CPU Detected\n");
		break;
	}
	return 0;
}

/* Intel Specific brand list */
char *Intel[] = {
	"Brand ID Not Supported.",
	"Intel(R) Celeron(R) processor",
	"Intel(R) Pentium(R) III processor",
	"Intel(R) Pentium(R) III Xeon(R) processor",
	"Intel(R) Pentium(R) III processor",
	"Reserved",
	"Mobile Intel(R) Pentium(R) III processor-M",
	"Mobile Intel(R) Celeron(R) processor",
	"Intel(R) Pentium(R) 4 processor",
	"Intel(R) Pentium(R) 4 processor",
	"Intel(R) Celeron(R) processor",
	"Intel(R) Xeon(R) Processor",
	"Intel(R) Xeon(R) processor MP",
	"Reserved",
	"Mobile Intel(R) Pentium(R) 4 processor-M",
	"Mobile Intel(R) Pentium(R) Celeron(R) processor",
	"Reserved",
	"Mobile Genuine Intel(R) processor",
	"Intel(R) Celeron(R) M processor",
	"Mobile Intel(R) Celeron(R) processor",
	"Intel(R) Celeron(R) processor",
	"Mobile Geniune Intel(R) processor",
	"Intel(R) Pentium(R) M processor",
	"Mobile Intel(R) Celeron(R) processor"
};

/* This table is for those brand strings that have two values depending on the processor signature. It should have the same number of entries as the above table. */
char *Intel_Other[] = {
	"Reserved",
	"Reserved",
	"Reserved",
	"Intel(R) Celeron(R) processor",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Intel(R) Xeon(R) processor MP",
	"Reserved",
	"Reserved",
	"Intel(R) Xeon(R) processor",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

/*
 * APIC ("Advanced Programmable Interrupt Controller") is the
 * updated Intel standard for the older PIC. It is used in
 * multiprocessor systems and is an integral part of all recent
 * Intel (and compatible) processors.
 */
bool has_apic(void)
{
	unsigned long eax, ebx, ecx, edx;
	cpuid(1, eax, ebx, ecx, edx);
	return ((edx & APIC) == APIC);
}

/*
 * Processors from the P6 family onwards (including PentiumPro, Pentium II, III, 4 and Intel Core)
 * have a collection of registers that allow configuration of OS-relevant things such as memory type-range,
 * sysenter/sysexit, local APIC, etc. These MSRs are accessed using special instructions such as RDMSR (Read MSR),
 * WRMSR (Write MSR), and RDTSC.
 */
bool has_msr(void)
{
	unsigned long eax, ebx, ecx, edx;
	cpuid(1, eax, ebx, ecx, edx);
	return ((edx & MSR) == MSR);
}

/* Intel-specific information */
int do_intel(void) {
	kdbg_log("Intel Specific Features:\n");
	unsigned long eax, ebx, ecx, edx, max_eax, signature, unused;
	int model, family, type, brand, stepping, reserved;
	int extended_family = -1;
	cpuid(1, eax, ebx, ecx, edx);
	kdbg_log("CPU features (ECX): 0x%x\n", ecx);
	kdbg_log("CPU features (EDX): 0x%x\n", edx);
	kdbg_log("CPU features:\n");
	if((ecx & SSE3) == SSE3)		kdbg_log("SSE3 Streaming SIMD Extensions 3\n");
	if((ecx & DTE64) == DTE64)		kdbg_log("64-Bit Debug Store\n");
	if((ecx & MONITOR) == MONITOR)	kdbg_log("The processor supports the MONITOR and MWAIT instructions\n");
	if((ecx & DS_CPL) == DS_CPL)	kdbg_log("CPL Qualified Debug Store\n");
	if((ecx & VMX) == VMX)			kdbg_log("Virtual Machine Extensions\n");
	if((ecx & SMX) == SMX)			kdbg_log("Safer Mode Extensions\n");
	if((ecx & EST) == EST)			kdbg_log("Enhanced Intel SpeedStep®\n");
	if((ecx & TM2) == TM2)			kdbg_log("Thermal Monitor\n");
	if((ecx & SSSE3) == SSSE3)		kdbg_log("Supplemental Streaming SIMD Extensions 3\n");
	if((ecx & CNXT_ID) == CNXT_ID)	kdbg_log("Context ID The L1 data cache mode can be set to either adaptive mode or shared mode by the BIOS\n");
	if((ecx & CX16) == CX16)		kdbg_log("CMPXCHG16B This processor supports the CMPXCHG16B instruction\n");
	if((ecx & XTPR) == XTPR)		kdbg_log("Send Task Priority Messages\n");
	if((ecx & PDCM) == PDCM)		kdbg_log("Performance Capabilities MSR\n");
	if((ecx & DCA) == DCA)			kdbg_log("Direct Cache Access\n");
	if((ecx & SSE4_1) == SSE4_1)	kdbg_log("Streaming SIMD Extensions 4.1\n");
	if((ecx & SSE4_2) == SSE4_2)	kdbg_log("Streaming SIMD Extensions 4.2\n");
	if((edx & FPU) == FPU) 			kdbg_log("Floating point unit present\n");
	if((edx & VME) == VME)			kdbg_log("Virtual mode extension\n");
	if((edx & DE) == DE) 			kdbg_log("Debugging extension\n");
	if((edx & PSE) == PSE) 			kdbg_log("Page size extension\n");
	if((edx & TSC) == TSC)			kdbg_log("Timestamp counter\n");
	if((edx & MSR) == MSR) 			kdbg_log("Model specific registers\n");
	if((edx & PAE) == PAE)			kdbg_log("Physical address extension\n");
	if((edx & MCE) == MCE) 			kdbg_log("Machine check extension\n");
	if((edx & CX8) == CX8) 			kdbg_log("CMPXCHG8 instruction supported\n");
	if((edx & APIC) == APIC)		kdbg_log("On-chip APIC hardware support\n");
	if((edx & SEP) == SEP) 			kdbg_log("Fast system call\n");
	if((edx & MTRR) == MTRR)		kdbg_log("Memory type range registers\n");
	if((edx & PGE) == PGE) 			kdbg_log("Page global enable\n");
	if((edx & MCA) == MCA) 			kdbg_log("Machine check architecture\n");
	if((edx & CMOV) == CMOV)		kdbg_log("Conditional move instruction supported\n");
	if((edx & PAT) == PAT) 			kdbg_log("Page attribute table\n");
	if((edx & PSE_36) == PSE_36)	kdbg_log("36-bit page size extension\n");
	if((edx & PSN) == PSN) 			kdbg_log("Processor serial number\n");
	if((edx & CLFSH) == CLFSH) 		kdbg_log("CLFLUSH instruction supported\n");
	if((edx & DS) == DS)			kdbg_log("Debug store\n");
	if((edx & ACPI) == ACPI) 		kdbg_log("Thermal monitor and software controlled clock facilities supported\n");
	if((edx & MMX) == MMX)			kdbg_log("Intel architecture MMX supported\n");
	if((edx & FXSR) == FXSR) 		kdbg_log("Fast floating point save and restore\n");
	if((edx & SSE) == SSE) 			kdbg_log("Streaming SIMD extensions supported\n");
	if((edx & SSE2) == SSE2)		kdbg_log("Streaming SIMD extensions 2\n");
	if((edx & SS) == SS) 			kdbg_log("Self-snoop\n");
	if((edx & HTT) == HTT)			kdbg_log("Multi-threading\n");
	if((edx & TM) == TM) 			kdbg_log("Thermal monitor supported\n");
	if((edx & IA64) == IA64) 		kdbg_log("IA64 capabilities\n");
	if((edx & PBE) == PBE)			kdbg_log("Pending break enable\n");

	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	type = (eax >> 12) & 0x3;
	brand = ebx & 0xff;
	stepping = eax & 0xf;
	reserved = eax >> 14;
	signature = eax;
	kdbg_log("Type %d - ", type);
	switch(type) {
		case 0:
			kdbg_log("Original OEM");
		break;
		case 1:
			kdbg_log("Overdrive");
		break;
		case 2:
			kdbg_log("Dual-capable");
		break;
		case 3:
			kdbg_log("Reserved");
		break;
	}
	kdbg_log("\n");
	kdbg_log("Family %d - ", family);
	switch(family) {
		case 3:
			kdbg_log("i386");
		break;
		case 4:
			kdbg_log("i486");
		break;
		case 5:
			kdbg_log("Pentium");
		break;
		case 6:
			kdbg_log("Pentium Pro");
		break;
		case 15:
			kdbg_log("Pentium 4");
	}
	kdbg_log("\n");
	if(family == 15) {
		extended_family = (eax >> 20) & 0xff;
		kdbg_log("Extended family %d\n", extended_family);
	}
	kdbg_log("Model %d - ", model);
	switch(family) {
		case 3:
		break;
		case 4:
		switch(model) {
			case 0:
			case 1:
				kdbg_log("DX");
			break;
			case 2:
				kdbg_log("SX");
			break;
			case 3:
				kdbg_log("487/DX2");
			break;
			case 4:
				kdbg_log("SL");
			break;
			case 5:
				kdbg_log("SX2");
			break;
			case 7:
				kdbg_log("Write-back enhanced DX2");
			break;
			case 8:
				kdbg_log("DX4");
			break;
		}
		break;
		case 5:
		switch(model) {
			case 1:
				kdbg_log("60/66");
			break;
			case 2:
				kdbg_log("75-200");
			break;
			case 3:
				kdbg_log("for 486 system");
			break;
			case 4:
				kdbg_log("MMX");
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
				kdbg_log("Pentium Pro");
			break;
			case 3:
				kdbg_log("Pentium II Model 3");
			break;
			case 5:
				kdbg_log("Pentium II Model 5/Xeon/Celeron");
			break;
			case 6:
				kdbg_log("Celeron");
			break;
			case 7:
				kdbg_log("Pentium III/Pentium III Xeon - external L2 cache");
			break;
			case 8:
				kdbg_log("Pentium III/Pentium III Xeon - internal L2 cache");
			break;
		}
		break;
		case 15:
		break;
	}
	kdbg_log("\n");

	/* TODO: cache descriptors */
	//cpuid(2, eax, ebx, ecx, edx);


	cpuid(0x80000000, max_eax, unused, unused, unused);
	/* Quok said: If the max extended eax value is high enough to support the processor brand string
	(values 0x80000002 to 0x80000004), then we'll use that information to return the brand information.
	Otherwise, we'll refer back to the brand tables above for backwards compatibility with older processors.
	According to the Sept. 2006 Intel Arch Software Developer's Guide, if extended eax values are supported,
	then all 3 values for the processor brand string are supported, but we'll test just to make sure and be safe. */
	if(max_eax >= 0x80000004) {
		kdbg_log("Brand: ");
		if(max_eax >= 0x80000002) {
			cpuid(0x80000002, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000003) {
			cpuid(0x80000003, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		if(max_eax >= 0x80000004) {
			cpuid(0x80000004, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		kdbg_log("\n");
	} else if(brand > 0) {
		kdbg_log("Brand %d - ", brand);
		if(brand < 0x18) {
			if(signature == 0x000006B1 || signature == 0x00000F13) {
				kdbg_log("%s\n", Intel_Other[brand]);
			} else {
				kdbg_log("%s\n", Intel[brand]);
			}
		} else {
			kdbg_log("Reserved\n");
		}
	}
	kdbg_log("Stepping: %d Reserved: %d\n", stepping, reserved);
	return 0;
}

/* Print Registers */
void printregs(int eax, int ebx, int ecx, int edx) {
	int j;
	char string[17];
	string[16] = '\0';
	for(j = 0; j < 4; j++) {
		string[j] = eax >> (8 * j);
		string[j + 4] = ebx >> (8 * j);
		string[j + 8] = ecx >> (8 * j);
		string[j + 12] = edx >> (8 * j);
	}
	kdbg_log("%s", string);
}

/* AMD-specific information */
int do_amd(void) {
	kdbg_log("AMD Specific Features:\n");
	unsigned long extended, eax, ebx, ecx, edx, unused;
	int family, model, stepping, reserved;
	cpuid(1, eax, unused, unused, unused);
	model = (eax >> 4) & 0xf;
	family = (eax >> 8) & 0xf;
	stepping = eax & 0xf;
	reserved = eax >> 12;
	kdbg_log("Family: %d Model: %d [", family, model);
	switch(family) {
		case 4:
			kdbg_log("486 Model %d", model);
		break;
		case 5:
		switch(model) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 6:
			case 7:
				kdbg_log("K6 Model %d", model);
			break;
			case 8:
				kdbg_log("K6-2 Model 8");
			break;
			case 9:
				kdbg_log("K6-III Model 9");
			break;
			default:
				kdbg_log("K5/K6 Model %d", model);
			break;
		}
		break;
		case 6:
		switch(model) {
			case 1:
			case 2:
			case 4:
				kdbg_log("Athlon Model %d", model);
			break;
			case 3:
				kdbg_log("Duron Model 3");
			break;
			case 6:
				kdbg_log("Athlon MP/Mobile Athlon Model 6");
			break;
			case 7:
				kdbg_log("Mobile Duron Model 7");
			break;
			default:
				kdbg_log("Duron/Athlon Model %d", model);
			break;
		}
		break;
	}
	kdbg_log("]\n");
	cpuid(0x80000000, extended, unused, unused, unused);
	if(extended == 0) {
		return 0;
	}
	if(extended >= 0x80000002) {
		unsigned int j;
		kdbg_log("Detected Processor Name: ");
		for(j = 0x80000002; j <= 0x80000004; j++) {
			cpuid(j, eax, ebx, ecx, edx);
			printregs(eax, ebx, ecx, edx);
		}
		kdbg_log("\n");
	}
	if(extended >= 0x80000007) {
		cpuid(0x80000007, unused, unused, unused, edx);
		if(edx & 1) {
			kdbg_log("Temperature Sensing Diode Detected!\n");
		}
	}
	kdbg_log("Stepping: %d Reserved: %d\n", stepping, reserved);
	return 0;
}

