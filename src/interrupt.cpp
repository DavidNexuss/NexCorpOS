#include "interrupt.h"
#include "pic.h"

extern "C" {
    #include "stdout.h"
    #include "keyboard.h"
    #include "ports.h"
}
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

InterruptManager::InterruptManager(GlobalDescriptorTable &gdt){

    const uint8_t IDT_INTERRUPT_GATE = 0xE;
    uint16_t codeSegment = gdt.CodeSegmentSelector();

    for (uint16_t i = 0; i < 256; i++)
        SetInterruptDescriptorTableEntry(i,codeSegment, &int_bottom,0,IDT_INTERRUPT_GATE);
    
    
    SetInterruptDescriptorTableEntry(0x20,codeSegment, &handleInterruptRequest0x20,0,IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x21,codeSegment, &handleInterruptRequest0x21,0,IDT_INTERRUPT_GATE);
    
    interruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interruptDescriptorTable;

    load_idt(&idt);
}
void InterruptManager::ignoreInterruptRequest(){}

void InterruptManager::Activate(){
    
    asm("sti");
}
InterruptManager::~InterruptManager(){}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp){

    
    switch (interruptNumber)
    {
    case KEYBOARD_INTERRUPT_NUMBER:
        keyboard_handler();
        break;
    
    default:
        ignoreInterruptRequest();
        break;
    }
    return esp;
}