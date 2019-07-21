#pragma once
#include "types.h"
#include "gdt.h"
class InterruptManager{

    protected:
        struct GateDescriptor{
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBits;

        }__attribute__((packed));
        static GateDescriptor interruptDescriptorTable[256];

        struct interruptDescriptorTablePointer
        {
            uint16_t size;
            uint32_t base;
        }__attribute__((packed));

        static void SetInterruptDescriptorTableEntry(
            uint8_t interruptNumber,
            uint16_t codeSegmentSelectorOffset,
            void (*handler)(),
            uint8_t descriptorPriviliegeLevel,
            uint8_t descriptorType
        );
    
    public:

        InterruptManager(GlobalDescriptorTable *gdt);
        ~InterruptManager();

        void Activate();
        
        static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);
        
        static void ignoreInterruptRequest();

        static void handleInterruptRequest0x02(); //Not maskable interrupts
        
        static void handleInterruptRequest0x00(); //

        //Hardware interrupts
        static void handleInterruptRequest0x20();
        static void handleInterruptRequest0x21();
        static void handleInterruptRequest0x2C();
};