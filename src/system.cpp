#include "stdafx.h"
#include "system.h"

DriverManager* sys::driver_manager;
PCIController* sys::pci_controller;
KeyboardDriver* sys::keyboard_driver;
MouseDriver* sys::mouse_driver;
DebugScreen* sys::debug_screen;
COM_Manager* sys::com_manager;
InterruptManager* sys::interrupt_manager;
GlobalDescriptorTable* sys::global_descriptor_table;


void sleep(unsigned int t){

    t*= SLEEP;
    while(t--){}
}