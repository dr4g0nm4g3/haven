; irqs.s - contains IRQs 0 - 15
;
;@author Jeff DiClemente
;@date 09/12/2008

	[BITS 32]
	global _irq0:function
	global _irq1:function
	global _irq2:function
	global _irq3:function
	global _irq4:function
	global _irq5:function
	global _irq6:function
	global _irq7:function
	global _irq8:function
	global _irq9:function
	global _irq10:function
	global _irq11:function
	global _irq12:function
	global _irq13:function
	global _irq14:function
	global _irq15:function
	
	extern irq_handler

_irq0:
	cli
	push 0x0
	push byte 32
	jmp _irq_common_stub
	
_irq1:
	cli
	push byte 0
	push byte 33
	jmp _irq_common_stub
	
_irq2:
	cli
	push byte 0
	push byte 34
	jmp _irq_common_stub
	
_irq3:
	cli
	push byte 0
	push byte 35
	jmp _irq_common_stub
	
_irq4:
	cli
	push byte 0
	push byte 36
	jmp _irq_common_stub
	
_irq5:
	cli
	push byte 0
	push byte 37
	jmp _irq_common_stub
	
_irq6:
	cli
	push byte 0
	push byte 38
	jmp _irq_common_stub
	
_irq7:
	cli
	push byte 0
	push byte 39
	jmp _irq_common_stub
	
_irq8:
	cli
	push byte 0
	push byte 40
	jmp _irq_common_stub
	
_irq9:
	cli
	push byte 0
	push byte 41
	jmp _irq_common_stub

_irq10:
	cli
	push byte 0
	push byte 42
	jmp _irq_common_stub
	
_irq11:
	cli
	push byte 0
	push byte 43
	jmp _irq_common_stub
	
_irq12:
	cli
	push byte 0
	push byte 44
	jmp _irq_common_stub
	
_irq13:
	cli
	push byte 0
	push byte 45
	jmp _irq_common_stub
	
_irq14:
	cli
	push byte 0
	push byte 46
	jmp _irq_common_stub
	
_irq15:
	cli
	push byte 0
	push byte 47
	jmp _irq_common_stub

; common stub for all ISQs that calls a common function handler
_irq_common_stub:
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
	push eax
	mov eax, irq_handler
	call eax
	pop eax
	pop ds
	pop es
	pop fs
	pop gs
	popa
	add esp, 8									; clean up pushed ISR # and error code
	iret												; this is an interrupt handler, so return execution back and enable interrupts again