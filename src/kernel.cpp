#include "config.h"
#include "ui/widget.h"
#include "ui/session.h"
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
#include "cpu/thread.h"
#include "types.h"
#include "util/list.h"

#include "drivers/driver_vga.h"

/*
*  kernel.cpp
*/

extern "C"{
	
	void kernelLoop(){

	//	while(1) {}
	}
	
	void kmain(void)
	{
	
	char *vidptr = (char*)0xb8000; 	//video mem begins here.
	initstdout(vidptr);
	cls();
	println("Console started");
	
	//PageManager m;
	
	sys::global_descriptor_table = new GlobalDescriptorTable();
	sys::global_descriptor_table->flushGDT();

	initCommandDB();
	addDebugCommands();
	
	sys::init_pics();
	//Creating system Struct


	sys::task_manager = new TaskManager();
	sys::pci_controller = new PCIController();
    sys::driver_manager = new DriverManager();
    sys::pci_controller->selectDrivers(sys::driver_manager);
    
    sys::keyboard_driver = new KeyboardDriver();
    sys::mouse_driver = new MouseDriver();
    sys::vga_driver = new VGADriver();

    sys::driver_manager->addDriver(sys::keyboard_driver);
    sys::driver_manager->addDriver(sys::vga_driver);
	//sys::driver_manager->addDriver(sys::mouse_driver);

    sys::driver_manager->ActivateAll();

    #ifdef DEBUG
    println("System structure created");
    #endif

	//IDT
	 sys::interrupt_manager = new InterruptManager(sys::global_descriptor_table);
	//*******************DRIVERS*********************/
	//------------------END-SETUP---------------------

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

//	sys::task_manager->addTask(new Task((void*)kernelLoop));

	flush_irq_0(); //Start scheduling
	#endif

	#define GRAPHICS_MODE
	#ifdef GRAPHICS_MODE

	sys::vga_driver->SetMode(320,200,8);
	sys::ui::currentSession = new Session(1,ScreenMode(320,200,8));

	sys::ui::currentSession->renderAll();
	#endif
	while (1){

		#ifdef _ENABLE_GDB_STUB_
	//	putDebugChar('a');
		#endif
	}
	}
}
