section .text
global load_gdt
extern codeSegmentSelectortemp
extern dataSegmentSelectortemp

load_gdt:
    mov edx, [esp + 4]
    lgdt [edx]
    mov ax, 0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    jmp 0x8:update_registers
    
update_registers:
    ret