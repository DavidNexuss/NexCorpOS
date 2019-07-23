
;32BIT-------------------------------------------------------------------------
global read_port32
read_port32:
  	mov edx, [esp + 4]
  	in eax, dx
  	ret

global write_port32
write_port32:
  	mov   edx, [esp + 4]
  	mov   eax, [esp + 4 + 4]
  	out   dx, eax
  	ret

;16BIT-------------------------------------------------------------------------
global read_port16
read_port16:
  	mov edx, [esp + 4]
  	in ax, dx
  	ret

global write_port16
write_port16:
  	mov   edx, [esp + 4]
  	mov   eax, [esp + 4 + 4]
  	out   dx, ax
  	ret
;8BIT-------------------------------------------------------------------------
global read_port8
read_port8:
  	mov edx, [esp + 4]
  	in al, dx
  	ret

global write_port8
write_port8:
  	mov   edx, [esp + 4]
  	mov   al, [esp + 4 + 4]
  	out   dx, al
  	ret
