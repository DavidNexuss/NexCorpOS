#pragma once

#include "cpu/interrupt.h"
#include "memory/kmemory.h"
#include "drivers/driver_keyboard.h"
#include "drivers/driver_mouse.h"
#include "cpu/gdt.h"
#include "cpu/interrupt.h"
#include "hardware/pci.h"
#include "hardware/serial.h"
#include "debug/debug.h"

#define SLEEP 300000000

void sleep(unsigned int t);

namespace sys{

    extern DriverManager* driver_manager;
    extern PCIController* pci_controller;
    extern InterruptManager* interrupt_manager;
    extern KeyboardDriver* keyboard_driver;
    extern MouseDriver* mouse_driver;
    extern COM_Manager* com_manager;
    extern DebugScreen* debug_screen;
}