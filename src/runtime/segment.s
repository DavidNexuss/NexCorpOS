global getCurrentCodeSegment
global getCurrentDataSegment
global getCurrentStackSegment
global getCurrentStackPointer
getCurrentCodeSegment:
    mov ax,cs
    ret
getCurrentDataSegment:
    mov ax,ds
    ret
getCurrentStackSegment:
    mov ax,ss
    ret
getCurrentStackPointer:
    mov eax,esp
    ret