#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable():
nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,KERNELCODE_SEGMENTSELECTOR,0x9A),
dataSegmentSelector(0,KERNELDATA_SEGMENTSELECTOR,0x92)
{

    uint32_t i[2];
    i[0] = (uint32_t)this;
    i[1] = sizeof(GlobalDescriptorTable) << 16;

    load_gdt(*i);
}

GlobalDescriptorTable::~GlobalDescriptorTable(){}

uint16_t GlobalDescriptorTable::DataSegmentSelector(){

    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector(){

    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base,uint32_t limit,uint8_t flags){

    uint8_t* target = (uint8_t*)this;
    
}