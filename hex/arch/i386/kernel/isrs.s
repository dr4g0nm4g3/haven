; isrs.s - contains the ISRs (Interrupt Service Routines)
;
;@author Jeff DiClemente
;@date 08/07/2008

	[BITS 32]
	global _isr0:function
	global _isr1:function
	global _isr2:function
	global _isr3:function
	global _isr4:function
	global _isr5:function
	global _isr6:function
	global _isr7:function
	global _isr8:function
	global _isr9:function
	global _isr10:function
	global _isr11:function
	global _isr12:function
	global _isr13:function
	global _isr14:function
	global _isr15:function
	global _isr16:function
	global _isr17:function
	global _isr18:function
	global _isr19:function
	global _isr20:function
	global _isr21:function
	global _isr22:function
	global _isr23:function
	global _isr24:function
	global _isr25:function
	global _isr26:function
	global _isr27:function
	global _isr28:function
	global _isr29:function
	global _isr30:function
	global _isr31:function
	; syscall ISR
	;global _isr80:function

	; external function implemented in a c source file
	extern fault_handler

; Divide by zero
_isr0:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 0											; interrupt vector
	jmp _isr_common_stub

; Debug Exception
_isr1:
	cli														; disable interrupts
	push byte 0										; dummy error code
	push byte 1										; interrupt vector
	jmp _isr_common_stub
	
; Non Maskable Interrupt Exception
_isr2:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 2											; interrupt vector
	jmp _isr_common_stub

; Breakpoint Exception
_isr3:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 3											; interrupt vector
	jmp _isr_common_stub

; Into Detected Overflow Exception
_isr4:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 4											; interrupt vector
	jmp _isr_common_stub

; Out of Bounds Exception
_isr5:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 5											; interrupt vector
	jmp _isr_common_stub

; Invalid Opcode Exception
_isr6:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 6											; interrupt vector
	jmp _isr_common_stub

; No Coprocessor Exception
_isr7:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 7											; interrupt vector
	jmp _isr_common_stub

; Double Fault Exception
_isr8:
	cli														; disable interrupts
	push byte 8											; interrupt vector - NO dummy error  because this exception returns an error code!
	jmp _isr_common_stub

; Coprocessor Segment Overrun Exception
_isr9:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 9											; interrupt vector
	jmp _isr_common_stub

; Bad TSS Exception
_isr10:
	cli														; disable interrupts
	push byte 10										; interrupt vector - NO dummy error  because this exception returns an error code!
	jmp _isr_common_stub

; Segment Not Present Exception
_isr11:
	cli														; disable interrupts
	push byte 11										; interrupt vector - NO dummy error  because this exception returns an error code!
	jmp _isr_common_stub

; Stack Fault Exception
_isr12:
	cli														; disable interrupts
	push byte 12										; interrupt vector - NO dummy error  because this exception returns an error code!
	jmp _isr_common_stub

; General Protection Fault Exception
_isr13:
	cli														; disable interrupts
	push byte 13										; interrupt vector - NO dummy error  because this exception returns an error code!
	jmp _isr_common_stub

; Page Fault Exception
_isr14:
	cli														; disable interrupts
	push byte 14										; interrupt vector - NO dummy error  because this exception returns an error code!
	jmp _isr_common_stub

; Unknown Interrupt Exception
_isr15:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 15										; interrupt vector
	jmp _isr_common_stub

; Coprocessor Fault Exception
_isr16:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 16										; interrupt vector
	jmp _isr_common_stub

; Alignment Check Exception (486+)
_isr17:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 17										; interrupt vector
	jmp _isr_common_stub

; Machine Check Exception (Pentium/586+)
_isr18:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 18										; interrupt vector
	jmp _isr_common_stub
	
; Reserved
_isr19:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 19										; interrupt vector
	jmp _isr_common_stub

; Reserved
_isr20:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 20										; interrupt vector
	jmp _isr_common_stub

; Reserved
_isr21:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 21										; interrupt vector
	jmp _isr_common_stub

; Reserved
_isr22:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 22										; interrupt vector
	jmp _isr_common_stub
	
; Reserved
_isr23:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 23										; interrupt vector
	jmp _isr_common_stub
	
; Reserved
_isr24:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 24										; interrupt vector
	jmp _isr_common_stub
	
; Reserved
_isr25:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 25										; interrupt vector
	jmp _isr_common_stub

; Reserved
_isr26:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 26										; interrupt vector
	jmp _isr_common_stub

; Reserved
_isr27:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 27										; interrupt vector
	jmp _isr_common_stub

; Reserved
_isr28:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 28										; interrupt vector
	jmp _isr_common_stub
	
; Reserved
_isr29:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 29										; interrupt vector
	jmp _isr_common_stub
	
; Reserved
_isr30:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 30										; interrupt vector
	jmp _isr_common_stub
	
; Reserved
_isr31:
	cli														; disable interrupts
	push byte 0											; dummy error code
	push byte 31										; interrupt vector
	jmp _isr_common_stub

; common stub for all ISRs that calls a common function handler
; the C representation of this function would be: 
;			_isr_common_stub(unsigned char error_code, unsigned char num)
_isr_common_stub:
	pusha
	push gs
	push fs
	push es
	push ds
	mov ax, 0x10								; Kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp								; get stack pointer
	push eax										; push stack as a function parameter
	mov eax, fault_handler					
	call eax										; call fault_handler() function
	pop eax
	pop ds
	pop es
	pop fs
	pop gs
	popa
	add esp, 8									; clean up pushed ISR # and error code
	iret												; pops EIP, CS, EFLAGS, SS and ESP and enable interrupts again
	
