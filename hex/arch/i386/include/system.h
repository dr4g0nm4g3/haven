#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <apic.h>
#include <hktypes.h>
#include <idt.h>
#include <gdt.h>
#include <pit.h>

/*  contains data structures and function prototypes that pertain to the physical machine architecture */

/* macro to check flags. takes 1 and shifts it left 'bit' times */
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

/* commonly used values */
#define NULL 0
#define true 1
#define false 0
typedef int bool;


/* implementation in debug.s */
extern void _int1();
extern void _int3();
extern void _bochs_magic_break();
extern void _set_trace_flag();
extern void _clear_trace_flag();

/* task state segment */
typedef struct tss_s
{
	unsigned long prev_tss;	// The previous TSS - if we used hardware task switching this would form a linked list.
	unsigned long esp0;		// esp for ring 0
	unsigned long ss0;			// ss selector for ring 0
	unsigned long esp1;		// esp for ring 1
	unsigned long ss1;			// ss selector for ring 1
	unsigned long esp2;		// esp for ring 2
	unsigned long ss2;			// ss selector for ring 2
	unsigned long cr3;
	unsigned long eip;
	unsigned long eflags;
	unsigned long eax;
	unsigned long ecx;
	unsigned long edx;
	unsigned long ebx;
	unsigned long esp;
	unsigned long ebp;
	unsigned long esi;
	unsigned long edi;
	unsigned long es;
	unsigned long cs;
	unsigned long ss;
	unsigned long ds;
	unsigned long fs;
	unsigned long gs;
	unsigned long ldt;			// LDT segment selector
	unsigned short trap;
	unsigned short iomap_base;
} __attribute__((packed))tss_t;

/*
 * Represents the state of all the
 * CPU registers
 */
typedef struct cpu_state_s
{
	unsigned long eip;
	unsigned long eflags;
	unsigned long eax;
	unsigned long ecx;
	unsigned long edx;
	unsigned long ebx;
	unsigned long esp;
	unsigned long ebp;
	unsigned long esi;
	unsigned long edi;
	unsigned long es;
	unsigned long cs;
	unsigned long ss;
	unsigned long ds;
	unsigned long fs;
	unsigned long gs;
} __attribute__((packed))cpu_state_t;

/*
 * Represents a task
*/
typedef struct task_s
{
	uint64_t id;
	cpu_state_t cpu_state;
} __attribute__((packed))task_t;

/*
 * Represents a linked list of tasks
 */
typedef struct task_list_s
{
	task_t * pHead;
	task_t * pNext;
} task_list_t;

tss_t ring3_tss;

#define KERNEL_STACK_SIZE 2048       // Use a 2kb kernel stack.

/* Implemented in task.c */
void switch_to_user_mode();

/* implementation in tss.c */
void load_task_register(unsigned int seg_selector);
void init_tss(tss_t * sys_tss);
void set_ring0_stack(tss_t * sys_tss, unsigned long esp, unsigned long ss);


typedef enum
{	// feature bits found in the edx register after a call to CPUID with eax = 1
	FPU = 0x1,							/* FPU on-chip */
	VME = 0x2,							/* Virtual mode extension */
	DE = 0x4,							/* Debugging extension */
	PSE = 0x8,							/* Page size extension */
	TSC = 0x10,							/* Timestamp counter */
	MSR = 0x20,							/* Model specific registers */
	PAE = 0x40,							/* Physical address extension */
	MCE = 0x80,							/* Machine check extension */
	CX8 = 0x100,						/* CMPXCHG8 instruction supported */
	APIC = 0x200,						/* On-chip APIC hardware support */
	RESERVED = 0x400,					/* Reserved */
	SEP = 0x800,						/* Fast system call */
	MTRR= 0x1000,						/* Memory type range registers */
	PGE = 0x2000,						/* Page global enable */
	MCA = 0x4000,						/* Machine check architecture */
	CMOV = 0x8000,						/* Conditional move instruction supported */
	PAT = 0x10000,						/* Page attribute table */
	PSE_36 = 0x20000,					/* 36-bit page size extension */
	PSN = 0x40000,						/* Processor serial number is present */
	CLFSH = 0x80000,					/* CLFLUSH instruction supported */
	DS = 0x100000,						/* Debug store */
	ACPI = 0x200000,					/* Thermal monitor and software controlled clock facilities supported */
	MMX = 0x400000,						/* Intel architecture MMX supported */
	FXSR = 0x800000,					/* Fast floating point save and restore */
	SSE = 0x1000000,					/* Streaming SIMD extensions supported */
	SSE2 = 0x2000000,					/* Streaming SIMD extensions 2 */
	SS = 0x4000000,						/* Self-snoop */
	HTT = 0x8000000,					/* Multi-threading */
	TM = 0x10000000,					/* Thermal monitor supported */
	IA64 = 0x20000000,					/* IA64 capabilities */
	PBE = 0x40000000					/* Pending break enable */
} edx_feature_bits;

typedef enum
{	// feature bits found in the ecx register after a call to CPUID with eax = 1
	SSE3 = 0x1,							/*SSE3 Streaming SIMD Extensions 3 */
	RESERVED1 = 0x2,
	DTE64 = 0x4,						/* 64-Bit Debug Store */
	MONITOR = 0x8,						/* The processor supports the MONITOR and MWAIT instructions. */
	DS_CPL = 0x10,						/* CPL Qualified Debug Store */
	VMX = 0x20,							/* Virtual Machine Extensions */
	SMX = 0x40,							/* Safer Mode Extensions */
	EST = 0x80,							/* Enhanced Intel SpeedStep® */
	TM2 = 0x100,						/* Thermal Monitor */
	SSSE3 = 0x200,						/* Supplemental Streaming SIMD Extensions 3 */
	CNXT_ID = 0x400,					/* Context ID The L1 data cache mode can be set to either adaptive mode or shared mode by the BIOS. */
	RESERVED11 = 0x800,
	RESERVED12 = 0x1000,
	CX16 = 0x2000,						/* CMPXCHG16B This processor supports the CMPXCHG16B instruction. */
	XTPR = 0x4000,						/* Send Task Priority Messages */
	PDCM = 0x8000,						/* Performance Capabilities MSR */
	RESERVED16 = 0x10000,
	RESERVED17 = 0x20000,
	DCA = 0x40000,						/* Direct Cache Access */
	SSE4_1 = 0x80000,					/* Streaming SIMD Extensions 4.1 */
	SSE4_2 = 0x100000					/* Streaming SIMD Extensions 4.2 */
} ecx_feature_bits;

typedef struct cpu_info_s
{
	int model;
	int family;
	int type;
	int brand;
	int stepping;
	short speed;
	unsigned long feature_set_ecx;
	unsigned long feature_set_edx;
	short serial[4];
	char brand_id[48];
} cpu_info_t;

/* CPUID structure
typedef struct cpuid_s
{
	char vendor[13];
	char brand_id[48];
	short flags[4];
	short serial[4];
	short speed;
}__attribute__((packed)) cpuid_t; */

/* CMOS Structure */
typedef struct cmos_s
{
	char seconds;									/* 0x00*/					/* Seconds */
	char seconds_alarm;								/* 0x01*/					/* Seconds (alarm) */
	char minutes;									/* 0x02 */					/* Minutes */
	char minutes_alarm;								/* 0x03 */					/* Minutes (alarm) */
	char hours;										/* 0x04 */					/* Hours */
	char hours_alarm;								/* 0x05 */					/* Hours (alarm) */
	char day_of_week;								/* 0x06 */					/* Day of week */
	char day_of_month;								/* 0x07 */					/* Day of month */
	char month;										/* 0x08 */					/* Month */
	char year;										/* 0x09 */					/* Year */
	char a;											/* 0x0a*/					/* Status register A */
	char b;											/* 0x0b */					/* Status register B */
	char c;											/* 0x0c */					/* Status register C */
	char d;											/* 0x0d */					/* Status register D */
	char diagnosis;									/* 0x0e */					/* Diagnosis register */
	char shutdown;									/* 0x0f */					/* Shutdown status */
	char floppy;									/* 0x10 */					/* Floppy types */
	char reserved0;									/* 0x11 */					/* Reserved */
	char harddisk;									/* 0x12 */					/* Hard drive types */
	char reserved1;									/* 0x13 */					/* Reserved */
	char device;									/* 0x14 */					/* Device byte */
	short base_mem;									/* 0x15 - 0x16 */		/* Base memory */
	short ext_mem;									/* 0x17 - 0x18*/		/* Extended memory */
	char hdd1_ext;									/* 0x19 */					/* Extension for first HDD */
	char hdd2_ext;									/* 0x1a */					/* Extension for second HDD */
	char reserved2[5];								/* 0x1b - 0x1f */		/* Reserved */
	char hdd1_param[8];								/* 0x20 - 0x27 */ 	/* HDD one parameters */
	char reserved3[6];								/* 0x28 - 0x2d */		/* Reserved */
	short checksum;									/* 0x2e - 0x2f */		/* Checksum */
	short post_ext_mem;								/* 0x30 - 0x31 */		/* Post extended memory */
	char century;									/* 0x32 */					/* Century */
	short setup_info;								/* 0x33 - 0x34*/		/* Setup Information */
	char hdd2_param[8];								/* 0x35 */					/* HDD two parameters */
	char reserved4[3];								/* 0x3d - 0x3f */		/* Reserved */
}__attribute__((packed)) cmos_t;

/* cmos.c */
cmos_t * read_cmos();
void write_cmos(cmos_t * data);
void display_cmos(cmos_t * cmos);

/* cpuid.c */
int detect_cpu(void);
int do_intel(void);
int do_amd(void);
bool has_apic(void);
bool has_msr(void);
void printregs(int eax, int ebx, int ecx, int edx);

/*
 * store the amount of conventional memory, starting at address zero and with
 * a maximum value of 640K, and the amount of upper memory (starting above 1MB)
 * the fields represent the amount of memory in Kilobytes
 */
typedef struct sys_mem_total
{
	unsigned long lower_memKb;		//< amount of conventional memory in kilobytes
	unsigned long upper_memKb;		//< amount of upper memory in kilobytes
} sys_mem_total_t;

/*
 * holds individual memory regions of RAM.
 */
typedef struct sys_mem_region
{
	unsigned long base_addr_low;	//< lower 32-bits of the starting address of this memory region
	unsigned long base_addr_high;	//< upper 32-bits of the starting address of this memory region
	unsigned long length_low;		//< lower 32-bits of the size of this memory region
	unsigned long length_high;		//< upper 32-bits of the size of this memory region
} sys_mem_region_t;

void detect_memory(void * mbh);
void detect_devices(void * mbh);

#endif /*SYSTEM_H_*/
