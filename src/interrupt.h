#pragma once
#define IDT_SIZE 256

extern void load_idt(unsigned long *idt_ptr);
void idt_init();

void division_by_zero_handler();
extern void division_by_zero();
