extern division_by_zero_handler

global division_by_zero
division_by_zero:
	call division_by_zero_handler
	iretd

global load_idt
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret
