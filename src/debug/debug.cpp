#include "stdafx.h"
#include "debug/debug.h"
#include "runtime/segment.h"
#include "std/stdout.h"
#include "hardware/pci.h"
#include "system.h"
#include "memory/paging.h"
static uint16_t mapped = 0;
static void (*handler [12])();
static const char* names[12];

void printAllDebug(){

    printint(231);
    for (size_t i = 0; i < 12; i++)
    {
        if(mapped & (0b1 << i)){
            print("Debug Screen F");
            printint(i + 1);
            print(" ");
            print(names[i]);
            print(" ");
            printint((uint32_t)handler[i]);
        }
    }
    
}
DebugScreen::DebugScreen(){

    setHandler(0,printAllDebug,"Debug Map");
}
DebugScreen::~DebugScreen(){}

void DebugScreen::setHandler(uint32_t index,void (*func)(),const char* name){

    handler[index] = func;
    names[index] = name;

    mapped |= (0b1 << index);
}

void DebugScreen::handleKey(uint32_t index){

    cls();
    if(index == 0){

        cls();
    }

    if(index == 1){

        printAllMemoryBlocks();
    }

    if(index == 2){

        sys::pci_controller->printAllDevices();
    }

    if(index == 3){

        sys::printPageAddresses();
    }
}