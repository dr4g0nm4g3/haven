#ifndef GDT_H_
#define GDT_H_

/* data structures for our GDT implementation */

/* a single GDT entry:
 * 0						  15 16								  31
 * ------------------------------------------------------------------
 * | limit 0:15  				| base 0:15
 * ------------------------------------------------------------------
 * 32						  47 48								  63
 * ------------------------------------------------------------------
 * | base 16:23    | access 0:7	| flags 0:4 | limit 16:19 | base 24:31
 * ------------------------------------------------------------------
 * */

/*
 * Access Byte:
 * 7	6:5		4 3		2	1	0
 * -------------------------------
 * P 	DPL 	S Exec 	DC	RW	Ac
 * -------------------------------
 *
 * P 	-> Present bit. This must be 1 for all valid selectors.
 * DPL ->  Descriptor privilege level, 2 bits. Contains the ring level,
 * 			0 = highest (kernel), 3 = lowest (user applications)
 * S	-> Descriptor type. ( 0 = system. 1 = code or data).
 * Exec	-> Executable bit. 1 means this is a code segment.
 * 			0 means its a data segment.
 * DC	-> Direction bit/Conforming bit.
 * 			Direction bit for data selectors: Tells the direction. 0 the segment grows up. 1 the segment grows down
 * 			(i.e. the offset has to be greater than the base).
 * 			Conforming bit for code selectors:
 * 			If 1 code in this segment can be executed from an equal or lower privilege level.
 * 			For example, code in ring 3 can far-jump to conforming code in a ring 2 segment.
 * 			The priv-bits represent the highest privilege level that is allowed to execute the segment.
 * 			For example, code in ring 0 cannot far-jump to a conforming code segment with privl==0x2, while code in ring 2 and 3 can.
 * 			Note that the privilege level remains the same, ie. a far-jump form ring 3 to a privl==2-segment remains in ring 3 after the jump.
 * 			If 0 code in this segment can only be executed from the ring set in privl.
 * RW	-> Readable/Writable bit. Write access is never allowed for code segments.
 * 			Read access is always allowed for data segments.
 * Ac	-> Accessed bit. Always initially set to 0. The accessed bit indicates whether the segment has been accessed since the last
 * 			time the operating-system or executive cleared the bit. The processor sets this bit
 * 			whenever it loads a segment selector for the segment into a segment register,
 * 			assuming that the type of memory that contains the segment descriptor supports
 * 			processor writes. The bit remains set until explicitly cleared. This bit can be used both
 * 			for virtual memory management and for debugging.
 *
 * Flags High Nibble:
 * 7	6		5 4
 * -----------------
 * Gr	Size	L AVL
 * -----------------
 *
 * Gr	-> Granularity bit.
 * 			If 0 the limit is in 1 B blocks (byte granularity), if 1 the limit is in 4 KiB blocks (page granularity).
 * Size	-> Size bit. If 0 the selector defines 16 bit protected mode.
 * 			If 1 it defines 32 bit protected mode. You can have both 16 bit and 32 bit selectors at once.
 * L	-> 64-bit code segment flag (IA-32e mode only).
 * AVL	-> Available for use by system software. reserved.
 *
 */

// Each define here is for a specific bit in the descriptor.
// Refer to the Intel documentation for a description of what each one does.
#define SEG_CODE_DATA_TYPE 0x10 	// code/data Descriptor type (0 for system, 1 for code/data)
#define SEG_PRESENT  		0x80 	// Segment is Present
#define SEG_PRIV_RING0		0x00	// bits 5 and 6 are not set
#define SEG_PRIV_RING1		0x20	// bit 5 is set
#define SEG_PRIV_RING2		0x40	// bit 6 is set
#define SEG_PRIV_RING3		0x60	// bit 5 and 6 are set

// flags defined in the high nibble
#define GDT_FLAG_SAVL  	0x10 	// Available for system use
#define GDT_FLAG_LONG  	0x20 	// Long mode
#define GDT_FLAG_SIZE  	0x40 	// Size (0 for 16-bit, 1 for 32)
#define GDT_FLAG_GRAN  	0x80 	// Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)


/*
 * Definitions for all valid combinations of the 4 bits (i.e. the 'Type field')
 * in the 'access byte' (bits 0:3). These values only have
 * meaning when the Descriptor type (bit 4) is set to 1 (i.e. code or data).
 */
#define SEG_DATA_RD        0x00 	// Read-Only
#define SEG_DATA_RDA       0x01 	// Read-Only, accessed
#define SEG_DATA_RDWR      0x02 	// Read/Write
#define SEG_DATA_RDWRA     0x03 	// Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 	// Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 	// Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 	// Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 	// Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 	// Execute-Only
#define SEG_CODE_EXA       0x09 	// Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A 	// Execute/Read
#define SEG_CODE_EXRDA     0x0B 	// Execute/Read, accessed
#define SEG_CODE_EXC       0x0C 	// Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D 	// Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E 	// Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F 	// Execute/Read, conforming, accessed

/*
 * Definitions for all valid combinations of the 4 bits (i.e. the 'Type field')
 * in the 'access byte' (bits 0:3). These values only have
 * meaning when the Descriptor type (bit 4) is set to 0 (i.e. system).
 */
#define SEG_SYS_RESERVED	0x00	// Reserved
#define SEG_SYS_16BIT_TSS	0x01	// 16-bit TSS (Available)
#define SEG_SYS_LDT		0x02	// LDT
#define SEG_SYS_16BIT_TSSB	0x03	// 16-bit TSS (Busy)
#define SEG_SYS_16BIT_CG	0x04	// 16-bit Call Gate
#define SEG_SYS_TG			0x05	// Task Gate
#define SEG_SYS_16BIT_IG	0x06	// 16-bit Interrupt Gate
#define SEG_SYS_16BIT_TG	0x07	// 16-bit Trap Gate
#define SEG_SYS_RESERVED2	0x08	// Reserved
#define SEG_SYS_32BIT_TSSA	0x09	// 32-bit TSS (Available)
#define SEG_SYS_RESERVED3	0X0A	// Reserved
#define SEG_SYS_32BIT_TSSB	0x0B	// 32-bit TSS (Busy)
#define SEG_SYS_32BIT_CG	0x0C	// 32-bit Call Gate
#define SEG_SYS_RESERVED4	0x0D	// Reserved
#define SEG_SYS_32BIT_IG	0xoE	// 32-bit Interrupt Gate
#define SEG_SYS_32BIT_TG	0x0F	// 32-bit Trap Gate

/*
 * 32-bit GDT data structure. This represents the contents
 * of a GDT entry in memory.
 */
typedef struct gdt_entry_s 
{
	unsigned short limit;
	unsigned short base_address_low;
	unsigned char base_address_middle;
	unsigned char access;
	unsigned char granularity;		/* contains contents of flags and limit 16:19 */
	unsigned char base_address_high;
	
} __attribute__((packed))gdt_entry;

/* pointer to our GDT */
typedef struct gdt_ptr_s
{
	unsigned short limit;
	unsigned int address;
}__attribute__((packed))gdt_ptr;

/*
 * global GDT array and pointer to our GDT.
 * NOTE: this array needs to be expanded when/if
 * new GDT entries are required.
 * TODO: allocate the GDT dynamically on kernel startup.
 */
gdt_entry gdt[6];
gdt_ptr pgdt;


/* implemented in hloader.s */
/*
 * reloads the GDT table into memory
 */
extern void _gdt_flush();

/* function prototypes */

/*
 * Sets a GDT entry at a given index, entry_num, in the global GDT array
 * \param entry_num[in] - index into the global GDT array
 * \param base_address[in] - pointer to the base address of the GDT's segment
 * \param limit[in] - maximum size, in bytes, of the GDT's segment
 * \param access[in] - Bits describing the descriptor's attributes
 * \param flags[in] - Bits describing the descriptor's attributes
 */
void set_gdt_gate(int entry_num, unsigned long base_address, unsigned long limit, unsigned char access, unsigned char flags);

/*
 * initializes the global GDT array and creates the default
 * GDT entries for the kernel
 */
void gdt_install();

#endif /*GDT_H_*/
