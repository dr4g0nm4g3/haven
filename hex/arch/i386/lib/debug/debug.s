; debug.s - test int 1 and int 3 interrupts for debugging

[BITS 32]

global _int1:function
global _int3:function
global _bochs_magic_break:function
global _set_trace_flag:function
global _clear_trace_flag:function

[section .text]

; single step (debug) interrupt
_int1:
	int 1
	ret

; breakpoint interrupt
_int3:
	int 3
	ret

; Bochs specific: magic breakpoint trigger.
; must set "magic_break: enabled=1" in bochs
; config file for this to work.
_bochs_magic_break:
	xchg bx, bx
	ret

; set the trace bit in EFLAGS to turn on single step
_set_trace_flag:
	push eax
	pushf					; push EFLAGS value onto the stack
	pop eax				; pop EFLAGS value into eax to modify
	or eax, 0x100		; set the trace bit
	push eax				; push new EFLAGS value onto the stack
	popf						; pop the new value into EFLAGS
	pop eax
	ret

; clear the trace bit in EFLAGS to turn off single step
_clear_trace_flag:
	push eax
	pushf					; push EFLAGS value onto the stack
	pop eax				; pop EFLAGS value into eax to modify
	xor eax, 0x100	; clear the trace bit
	push eax				; push new EFLAGS value onto the stack
	popf						; pop the new value into EFLAGS
	pop eax
	ret
