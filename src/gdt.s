section .text
global load_gdt

load_gdt:
    mov edx, [esp + 4]
    lgdt [edx]
    ret