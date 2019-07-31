global fillPagingTables4kb

fillPagingTables4kb:
mov eax, 0x0
mov ebx, [esp + 4]
mov ecx, [esp + 4 + 4]
mov dword [offset], ecx

.fill_table:
    mov ecx, ebx
    or ecx, 3
    mov edx, dword [offset]
    mov [edx+eax*4], ecx
    add ebx, 4096
    inc eax
    cmp eax, 1024
    je .end
    jmp .fill_table

.end:
    ret
global enablePageDirectory4kb
enablePageDirectory4kb:
    mov eax, [esp + 4]
    mov cr3, eax

    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax
    ret

section .data
    offset dd 0x0