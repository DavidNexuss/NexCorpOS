section .text

%macro HandleInterruptRequest 1
global _ZN16InterruptManager26handleInterruptRequest%1Ev

_ZN16InterruptManager26handleInterruptRequest%1Ev:
	mov dword [interruptnumber], $1
	jmp int_bottom
%endmacro

extern _ZN16InterruptManager15handleInterruptEhj

HandleInterruptRequest 0x20
HandleInterruptRequest 0x21

global load_idt
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret
int_bottom:

	pusha
	push ds
	push es
	push fs
	push gs
	push esp
	push dword [interruptnumber]
	call _ZN16InterruptManager15handleInterruptEhj
	
	mov eax, esp

	pop gs
	pop fs
	pop es
	pop ds
	popa
	
	iret

section .data
	interruptnumber dd 0x0