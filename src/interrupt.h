#define IDT_SIZE 256
extern void load_idt(unsigned long *idt_ptr);
void idt_init();
