extern "C"{
	#include "color.h"
	#include "stdout.h"
	#include "system.h"
	#include "kmemory.h"
}
#include "gdt.h"
#include "interrupt.h"
#include "pic.h"

/*
*  kernel.c
*/

void init(char* vidptr){

  /*Initialization*/

	initstdout(vidptr);
	cls();
	println("Console started");
	mem_init(); //Init heap
	
	GlobalDescriptorTable gdt;
  	gdt.flushGDT();
	printint(sizeof(GlobalDescriptorTable::SegmentDescriptor));
	print("GDT loaded  ");
	printint((uint32_t)&gdt); print(" Code Segment Selector: ");
	printint(gdt.CodeSegmentSelector()); print(" Data Segment Selector: ");
	printint(gdt.DataSegmentSelector());
	ln();
	sys::init_pics();
	println("PICs loaded");
	InterruptManager idt = InterruptManager(gdt);
	idt.Activate();
	kb_init();
//	idt_init();
	sleep(2);
	cls();
	while (1){}
	
}

extern "C"{
	void kmain(void)
	{

		char *vidptr = (char*)0xb8000; 	//video mem begins here.
		init(vidptr);
		return;
	}
}
