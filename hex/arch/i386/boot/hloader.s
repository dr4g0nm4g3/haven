;
; multiboot loader used by GRUB to load HEX kernel
;
; Jeff DiClemente
; 02/25/2007
	[BITS 32]
	global _start           		; making entry point visible to linker
	extern _main					; kernel entry

section .text
_start:
	jmp multiboot_entry

	align 4
multiboot_header:
   dd MAGIC
   dd FLAGS
   dd CHECKSUM

; setting up the Multiboot header - see GRUB docs for details
	MODULEALIGN 		equ  1<<0							; align loaded modules on page boundaries
	MEMINFO     		equ  1<<1     						; provide memory map
	VBE					equ  1<<2							; provide VBE support
	FLAGS       		equ  MODULEALIGN | MEMINFO | VBE	; this is the Multiboot 'flag' field
	MAGIC       		equ  0x1BADB002 					; 'magic number' lets bootloader find the header
	CHECKSUM    		equ -(MAGIC + FLAGS)				; checksum required

; reserve initial kernel stack space
	STACKSIZE 			equ 0x4000          				; that's 16k.

	global _gdt_flush										; allow C source to call this function
	extern pgdt												; find gdt_ptr struct in C source
_gdt_flush:
	lgdt [pgdt]
	mov ax, 0x10											; kernel data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2											; 0x8 is kernel code segment
flush2:
	ret

	global _idt_load										; allow C source to call this function
	extern pidt												; find idt_ptr struct in C source
_idt_load:
	lidt [pidt]												; load IDT
	ret

multiboot_entry:
	mov esp, stack + STACKSIZE 								; set up the stack
	push esp								; save stack pointer so we can move the stack to a known location later
   	push eax                     			; pass Multiboot magic number
   	push ebx                     			; pass Multiboot info structure

	cli										; turn off interrupts until we're done setting up our IDT/GDT and remapping the IRQs
   	call  _main                 			; call the kernel main function
_loop:
	hlt                          			; halt machine should kernel return
	jmp _loop								; infinte loop

section .bss
align 32
stack:
   	resb STACKSIZE     						; reserve 16k stack on a quadword boundary
