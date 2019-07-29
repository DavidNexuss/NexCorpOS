#include "stdafx.h"

#include "std/color.h"
#include "std/stdout.h"
#include "memory/kmemory.h"
#include "cpu/gdt.h"
#include "runtime/segment.h"
#include "system.h"
#include "cpu/interrupt.h"
#include "hardware/pic.h"
#include "hardware/serial.h"
#include "drivers/driver_keyboard.h"
#include "debug/gdb.h"
#include "hardware/pit.h"
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
	
	GlobalDescriptorTable gdt;
	gdt.flushGDT();

	mem_init(); //Init kernel heap
	sys::init_pics();
	
	//Creating system Struct

	g_system = new System();

	//IDT
	 g_system->interruptManager = new InterruptManager(&gdt);
	//*******************DRIVERS*********************/

	g_system->interruptManager->Activate();
	//------------------END-SETUP---------------------

	#ifndef _ENABLE_GDB_STUB_
	
	initGDBStub();
    print("Waiting for GDB connection...");
	__asm__("int3");
	#else
	g_system->interruptManager->Activate();
	#endif

	#ifdef DEBUG
	//printAllMemoryBlocks();
	//printint(g_system->pci.Read(0,0,0,0));
	print("Heap Blocks: ");
	printint(blockCount());
	#endif
	sleep(5);
	while (1){

		#ifdef _ENABLE_GDB_STUB_
	//	putDebugChar('a');
		#endif
	}
	}
}
