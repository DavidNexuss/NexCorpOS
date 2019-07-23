#include "stdafx.h"
#include "system.h"
#include "hardware/pic.h"
#include "hardware/port.h"
#include "cpu/interrupt.h"
#include "drivers/driver_keyboard.h"
#include "std/stdout.h"

extern "C" {void load_idt(void* idt_pointer);}
extern "C" {void int_bottom();}

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(
            uint8_t interruptNumber,
            uint16_t codeSegmentSelectorOffset,
            void (*handler)(),
            uint8_t descriptorPriviliegeLevel,
            uint8_t descriptorType
)
{

    const uint8_t IDT_DESC_PRESENT = 0x80;

    interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].handlerAddressHighBits = ((uint32_t)handler >> 16) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | descriptorType | ((descriptorPriviliegeLevel&3) << 5); 
    interruptDescriptorTable[interruptNumber].reserved = 0;
}

InterruptManager::InterruptManager(GlobalDescriptorTable *gdt){

    const uint8_t IDT_INTERRUPT_GATE = 0xE;
    uint16_t codeSegment = gdt->CodeSegmentSelector();

    for (uint16_t i = 0; i < 256; i++)
        SetInterruptDescriptorTableEntry(i,codeSegment, &handleInterruptRequest0x02,0,IDT_INTERRUPT_GATE);
    
    
    SetInterruptDescriptorTableEntry(0x00,codeSegment, &handleInterruptRequest0x00,0,IDT_INTERRUPT_GATE);
    
    SetInterruptDescriptorTableEntry(0x20,codeSegment, &handleInterruptRequest0x20,0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21,codeSegment, &handleInterruptRequest0x21,0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x2C,codeSegment, &handleInterruptRequest0x2C,0,IDT_INTERRUPT_GATE);
    
    interruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interruptDescriptorTable;

    load_idt(&idt);
}

void InterruptManager::ignoreInterruptRequest(){
}

void InterruptManager::Activate(){
    
    #ifdef DEBUG
    println("IDT activated");
    #endif
    asm("sti");
}
InterruptManager::~InterruptManager(){}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp){
    
    switch (interruptNumber)
    {
    case KEYBOARD_INTERRUPT_NUMBER:
        g_system->keyboard_driver->handleInterrupt();
        break;
    case MOUSE_INTERRUPT_NUMBER:
        g_system->mouse_driver->handleInterrupt();
    case 0x00:
        println("Can't divide by zero!");
        break;
    case 0x02:
        ignoreInterruptRequest();
        print("Not maskable interrupt!");
        ln();
        break;
    default:
        ignoreInterruptRequest();
        print("Ignore interrupt: ");
        printint(interruptNumber);
        ln();
        break;
    }

    CLEAR_EOI();
    return esp;
}