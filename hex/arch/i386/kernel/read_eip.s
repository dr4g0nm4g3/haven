; read_eip.s - quick way to get the instruction pointer and return it in eax
;	EAX is the 'return value' register for the __cdecl calling convention, so we are return EIP when calling from C code
;
; C function prototype:
;	unsigned long _read_eip();
;

[BITS 32]

global _read_eip:function

_read_eip:
	pop eax
	jmp eax
	