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
	sys::init_pics();
	
	//Creating system Struct

	g_system = new System();
	
	/*--------------Start SETUP------------------- */

	//GDT
	g_system->kernel_globalDescriptorTable = new GlobalDescriptorTable();
  	g_system->kernel_globalDescriptorTable->flushGDT();

	//PICs

	//IDT
	 g_system->interruptManager = new InterruptManager(g_system->kernel_globalDescriptorTable);
	//*******************DRIVERS*********************/

	g_system->keyboard_driver->Activate();
	g_system->mouse_driver->Activate();

	//------------------END-SETUP---------------------

	g_system->interruptManager->Activate();

	#ifdef DEBUG
	printAllMemoryBlocks();
	#endif
	sleep(5);
	while (1){}
	}
}
