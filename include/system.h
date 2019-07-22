#pragma once

#include "interrupt.h"
#include "kmemory.h"
#include "driver_keyboard.h"
#include "driver_mouse.h"
#include "gdt.h"
#include "interrupt.h"
#include "pci.h"
#include "vector.h"
#include "debug.h"

#define SLEEP 300000000

void sleep(unsigned int t);

class System{

    public:
        GlobalDescriptorTable* kernel_globalDescriptorTable;
        InterruptManager* interruptManager;

        KeyboardDriver* keyboard_driver;
        MouseDriver* mouse_driver;
        
        PCIController pci;
        DriverManager driver_manager;
        
        DebugScreen debugScreen;
        
        System();
        ~System();

};

static System* g_system;