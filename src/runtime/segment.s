global getCurrentCodeSegment
global getCurrentDataSegment
global getCurrentStackSegment
getCurrentCodeSegment:
    mov ax,cs
    ret
getCurrentDataSegment:
    mov ax,ds
    ret
getCurrentStackSegment:
    mov ax,ss
    ret
