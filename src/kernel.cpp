extern "C"{
	#include "color.h"
	#include "stdout.h"
	#include "system.h"
	#include "kmemory.h"
}
#include "gdt.h"
#include "interrupt.h"

/*
*  kernel.c
*/

void init(char* vidptr){

  /*Initialization*/

	initstdout(vidptr);
	cls();
	println("Console started");
  	printint(sizeof(GlobalDescriptorTable::SegmentDescriptor));
	GlobalDescriptorTable* gdt = new GlobalDescriptorTable();
	print("GDT loaded  ");
	printint((uint32_t)&gdt); print(" Code Segment Selector: ");
	printint(gdt->CodeSegmentSelector()); print(" Data Segment Selector: ");
	printint(gdt->DataSegmentSelector());
	ln();
	InterruptManager idt = InterruptManager(*gdt);
	idt.Activate();
//	idt_init();
	kb_init();
	mem_init();
	sleep(10);
	cls();
}

extern "C"{
	void kmain(void)
	{

		char *vidptr = (char*)0xb8000; 	//video mem begins here.
		init(vidptr);
		println("END INIT");
		while(1);
		return;
	}
}
