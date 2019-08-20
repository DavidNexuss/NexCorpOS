global geteip
geteip:
    mov eax,[esp + 4]
    ret
global killTask
killTask:
    int 0x20