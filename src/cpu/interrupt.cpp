#include "stdafx.h"
#include "system.h"
#include "hardware/pic.h"
#include "hardware/port.h"
#include "cpu/interrupt.h"
#include "drivers/driver_keyboard.h"
#include "std/stdout.h"
#include "cpu/cpu.h"
#include "runtime/segment.h"

extern "C" {void load_idt(void* idt_pointer);}
extern "C" {void int_bottom();}

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(
            uint8_t interruptNumber,
            uint16_t codeSegmentSelectorOffset,
            void* handler,
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
const uint8_t IDT_INTERRUPT_GATE = 0xE;
void InterruptManager::overrideInterruptGate(uint8_t interruptNumber,void* handler){

    print("Overriding interrupt: ");
    printhex(interruptNumber);
    ln();
    SetInterruptDescriptorTableEntry(interruptNumber,8,handler,0,IDT_INTERRUPT_GATE);
    interruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interruptDescriptorTable;

    load_idt(&idt);
}
InterruptManager::InterruptManager(GlobalDescriptorTable *gdt){

    uint16_t codeSegment = gdt->CodeSegmentSelector();
    codeSegmentDebug = codeSegment;

    for (uint16_t i = 0; i < 256; i++)
        SetInterruptDescriptorTableEntry(i,codeSegment,(void*)((uint32_t*) &handleInterruptRequest0x02),0,IDT_INTERRUPT_GATE);

    SetInterruptDescriptorTableEntry(0x01,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x01),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x02,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x02),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x03,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x03),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x04,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x04),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x00,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x00),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x05,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x05),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x06,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x06),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x07,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x07),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x08,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x08),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x09,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x09),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x10,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x10),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x11,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x11),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x12,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x12),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x13,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x13),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x14,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x14),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x15,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x15),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x16,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x16),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x17,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x17),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x18,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x18),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x19,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x19),0,IDT_INTERRUPT_GATE);

    SetInterruptDescriptorTableEntry(0x20,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x20),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x21),0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x2C,codeSegment, (void*)((uint32_t*)&handleInterruptRequest0x2C),0,IDT_INTERRUPT_GATE);

    interruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interruptDescriptorTable;

    load_idt(&idt);

    #ifdef DEBUG
    println("IDT loaded");
    #endif
}

void InterruptManager::ignoreInterruptRequest(){
}

InterruptManager::~InterruptManager(){}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp){


    sys::savedCPUState = (CPUState*)esp;
    switch (interruptNumber)
    {
    case KEYBOARD_INTERRUPT_NUMBER:
        sys::keyboard_driver->handleInterrupt();
        break;
    case MOUSE_INTERRUPT_NUMBER:
        println("mouse interrupt");
        sys::mouse_driver->handleInterrupt();
        break;
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