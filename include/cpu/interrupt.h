#pragma once
#include "types.h"
#include "cpu/gdt.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void enableInterrupts();
extern void disableInterrupts();
#ifdef __cplusplus
}
class InterruptManager{

    protected:
        uint16_t codeSegmentDebug;
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
            void *handler,
            uint8_t descriptorPriviliegeLevel,
            uint8_t descriptorType
        );
    
    public:

        InterruptManager(GlobalDescriptorTable *gdt);
        ~InterruptManager();

        void Activate();
        void overrideInterruptGate(uint8_t interruptNumber,void* handler);

        static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);
        
        static void ignoreInterruptRequest();

        
        static void handleInterruptRequest0x00(); // Divide by zero
        static void handleInterruptRequest0x01(); //
        static void handleInterruptRequest0x02(); // Not maskable interrupt
        static void handleInterruptRequest0x03(); //
        static void handleInterruptRequest0x04(); //
        static void handleInterruptRequest0x05(); //
        static void handleInterruptRequest0x06(); //
        static void handleInterruptRequest0x07(); //
        static void handleInterruptRequest0x08(); //
        static void handleInterruptRequest0x09(); //
        static void handleInterruptRequest0x10(); //
        static void handleInterruptRequest0x11(); //
        static void handleInterruptRequest0x12(); //
        static void handleInterruptRequest0x13(); //
        static void handleInterruptRequest0x14(); //
        static void handleInterruptRequest0x15(); //
        static void handleInterruptRequest0x16(); //
        static void handleInterruptRequest0x17(); //
        static void handleInterruptRequest0x18(); //
        static void handleInterruptRequest0x19(); //

        //Hardware interrupts
        static void handleInterruptRequest0x20();
        static void handleInterruptRequest0x21();
        static void handleInterruptRequest0x2C();
};

#endif