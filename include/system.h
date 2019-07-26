#pragma once

#include "cpu/interrupt.h"
#include "memory/kmemory.h"
#include "drivers/driver_keyboard.h"
#include "drivers/driver_mouse.h"
#include "cpu/gdt.h"
#include "cpu/interrupt.h"
#include "hardware/pci.h"
#include "hardware/serial.h"
#include "runtime/vector.h"
#include "debug/debug.h"

#define SLEEP 300000000

void sleep(unsigned int t);

class System{

    public:
        GlobalDescriptorTable* kernel_globalDescriptorTable;
        InterruptManager* interruptManager;

        KeyboardDriver* keyboard_driver;
        MouseDriver* mouse_driver;
        
        PCIController* pci;
        DriverManager driver_manager;
        COM_Manager com_manager;
        DebugScreen debugScreen;
        
        System();
        ~System();

};

static System* g_system;