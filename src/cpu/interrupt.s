section .text

%macro HandleInterruptRequest 1
global _ZN16InterruptManager26handleInterruptRequest%1Ev

_ZN16InterruptManager26handleInterruptRequest%1Ev:
	;mov dword [interruptnumber], %1

	push dword %1
	push ds
	push es
	push fs
	push gs
	push edi
	push esi
	push ebp
	push esp
	push edx
	push ecx
	push ebx
	push eax

	push esp
	push dword %1
	call _ZN16InterruptManager15handleInterruptEhj
	
	mov esp, eax
	
	pop eax;
    pop ebx;
    pop ecx;
    pop edx;
	add esp,4
	add esp,4
    pop esi;
    pop edi
	add esp,4
	add esp,4
	add esp,4
	add esp,4

	add esp,4
	iretd
%endmacro

extern _ZN16InterruptManager15handleInterruptEhj

HandleInterruptRequest 0x00;	Divide by zero
HandleInterruptRequest 0x01;
HandleInterruptRequest 0x02;    Not maskable interrupt
HandleInterruptRequest 0x03;
HandleInterruptRequest 0x04;
HandleInterruptRequest 0x05;
HandleInterruptRequest 0x06;
HandleInterruptRequest 0x07;
HandleInterruptRequest 0x08;
HandleInterruptRequest 0x09;
HandleInterruptRequest 0x10;
HandleInterruptRequest 0x11;
HandleInterruptRequest 0x12;
HandleInterruptRequest 0x13;
HandleInterruptRequest 0x14;
HandleInterruptRequest 0x15;
HandleInterruptRequest 0x16;
HandleInterruptRequest 0x17;
HandleInterruptRequest 0x18;
HandleInterruptRequest 0x19;
HandleInterruptRequest 0x20;
HandleInterruptRequest 0x21;
HandleInterruptRequest 0x2C;

global load_idt
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	ret
global enableInterrupts
enableInterrupts:
	sti
	ret
global disableInterrupts
disableInterrupts:
	cli
	ret

section .data
	interruptnumber dd 0x0