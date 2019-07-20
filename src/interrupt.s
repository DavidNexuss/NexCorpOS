section .text

%macro HandleInterruptRequest 1
global _ZN16InterruptManager26handleInterruptRequest%1Ev

_ZN16InterruptManager26handleInterruptRequest%1Ev:
	;mov dword [interruptnumber], %1
	
	pusha
	push ds
	push es
	push fs
	push gs
	push esp
	push dword %1
	call _ZN16InterruptManager15handleInterruptEhj
	
	mov esp, eax

	pop gs
	pop fs
	pop es
	pop ds
	popa
	
	iretd
%endmacro

extern _ZN16InterruptManager15handleInterruptEhj

HandleInterruptRequest 0x20
HandleInterruptRequest 0x21
HandleInterruptRequest 0x2C

global load_idt
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret
global int_bottom
int_bottom:

	pusha
	push ds
	push es
	push fs
	push gs
	push esp
	push dword [interruptnumber]
	call _ZN16InterruptManager15handleInterruptEhj
	
	mov esp, eax

	pop gs
	pop fs
	pop es
	pop ds
	popa
	
	iretd

section .data
	interruptnumber dd 0x0