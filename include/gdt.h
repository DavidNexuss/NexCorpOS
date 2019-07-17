#pragma once
#include "types.h"

#define KERNELCODE_SEGMENTSELECTOR 64*1024*1024 //64MB
#define KERNELDATA_SEGMENTSELECTOR 64*1024*1024 //64MB

#define GDT_TABLE_SIZE 3

extern "C"{void load_gdt(uint32_t gdt_pointer);}

class GlobalDescriptorTable{

    
    public:
        class SegmentDescriptor
        {
        private:
            uint16_t limit_lo;
            uint16_t base_lo;
            uint8_t base_hi;
            uint8_t type;
            uint8_t flags_limit_hi;
            uint8_t base_vhi;
        public:
            SegmentDescriptor(){};
            void setValues(uint32_t base, uint32_t limit, uint8_t type);

            uint32_t Base();
            uint32_t Limit();

        }__attribute__((packed));
    
    private:

    SegmentDescriptor gdt_table[GDT_TABLE_SIZE];

    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;
    SegmentDescriptor nullSegmentSelector;

    public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();
};