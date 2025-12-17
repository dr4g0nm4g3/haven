; syscalls.s - contains the ISRs (Interrupt Service Routine)
;	for system calls
;
;@author Jeff DiClemente
;@date 06/08/2014

	[BITS 32]
	; syscall ISR
	global _isr80:function

	; external function implemented in syscall.c
	extern syscall_handler

	; syscall ISR
_isr80:
	cli												; disable interrupts
	push byte 0										; push dummy error code onto the stack
	push 128										; interrupt vector
	jmp _syscall_common_stub

; common stub for all system calls that calls a common function handler
; the C representation of this function would be:
;			_syscall_common_stub(unsigned char error_code, unsigned char num)
_syscall_common_stub:
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
	push eax									; push stack as a function parameter
	mov eax, syscall_handler
	call eax									; call fault_handler() function
	pop eax
	pop ds
	pop es
	pop fs
	pop gs
	popa
	add esp, 8									; clean up pushed ISR # and error code
	iret										; pops EIP, CS, EFLAGS, SS and ESP and enable interrupts again
