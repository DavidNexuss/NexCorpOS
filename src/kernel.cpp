#include "stdafx.h"

#include "std/color.h"
#include "std/stdout.h"
#include "memory/kmemory.h"
#include "memory/paging.h"
#include "cpu/gdt.h"
#include "runtime/segment.h"
#include "system.h"
#include "runtime/shell.h"
#include "cpu/interrupt.h"
#include "hardware/pic.h"
#include "hardware/serial.h"
#include "drivers/driver_keyboard.h"
#include "debug/gdb.h"
#include "hardware/pit.h"
#include "types.h"
#include "util/list.h"

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
	
	PageManager m;
	GlobalDescriptorTable gdt;
	gdt.flushGDT();

	mem_init(); //Init kernel heap

	initCommandDB();
	addDebugCommands();
	
	sys::init_pics();
	//Creating system Struct

	sys::pci_controller = new PCIController();
    sys::driver_manager = new DriverManager();
    sys::pci_controller->selectDrivers(sys::driver_manager);
    
    sys::keyboard_driver = new KeyboardDriver();
    sys::mouse_driver = new MouseDriver();
    
    sys::driver_manager->addDriver(sys::keyboard_driver);
    sys::driver_manager->addDriver(sys::mouse_driver);

    sys::driver_manager->ActivateAll();

    #ifdef DEBUG
    println("System structure created");
    #endif

	//IDT
	 sys::interrupt_manager = new InterruptManager(&gdt);
	//*******************DRIVERS*********************/
	//------------------END-SETUP---------------------

	PIT_Manager manager;
	manager.sleep(200000);

	#ifdef _ENABLE_GDB_STUB_
	
		initGDBStub();
    	println("Waiting for GDB connection...");
		enableInterrupts();
		//__asm__("int3");
	#else
	enableInterrupts();
	#endif

	#ifdef DEBUG
	//printAllMemoryBlocks();
	//printint(g_system->pci.Read(0,0,0,0));

	
	#endif
	sleep(5);
	while (1){

		#ifdef _ENABLE_GDB_STUB_
	//	putDebugChar('a');
		#endif
	}
	}
}
