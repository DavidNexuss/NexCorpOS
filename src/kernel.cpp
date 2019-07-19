#include "stdafx.h"

#include "color.h"
#include "stdout.h"
#include "kmemory.h"
#include "gdt.h"

#include "system.h"
#include "interrupt.h"
#include "pic.h"
#include "driver_keyboard.h"
/*
*  kernel.cpp
*/

extern "C"{
	void kmain(void)
	{
	
	char *vidptr = (char*)0xb8000; 	//video mem begins here.
	initstdout(vidptr);
	cls();
	println("Console started");
	
	mem_init(); //Init kernel heap

	//Creating system Struct

	g_system = new System();
	
	/*--------------Start SETUP------------------- */

	//GDT
	GlobalDescriptorTable gdt;
  	gdt.flushGDT();

	//PICs
	sys::init_pics();


	//IDT
	InterruptManager idt = InterruptManager(gdt);
	idt.Activate();

	//*******************DRIVERS*********************/

	g_system->keyboard_driver->Activate();

	//------------------END-SETUP---------------------

	sleep(20);
	cls();
	while (1){}

	}
}
