#include "stdafx.h"
#include "gdt.h"
#include "stdout.h"

GlobalDescriptorTable::GlobalDescriptorTablePointer gdt_pointer;

uint16_t codeSegmentSelectortemp;
uint16_t dataSegmentSelectortemp;

size_t kernelCodeSegmentSelectorindex = 1;
size_t kernelDataSegmentSelectorindex = 2;

GlobalDescriptorTable::GlobalDescriptorTable()
{

    nullSegmentSelector.setValues(0,0,0);
    codeSegmentSelector.setValues(0,KERNELCODE_SEGMENTSELECTOR,0x9A);
    dataSegmentSelector.setValues(0,KERNELDATA_SEGMENTSELECTOR,0x92);

    gdt_table[0] = nullSegmentSelector;
    gdt_table[kernelCodeSegmentSelectorindex] = codeSegmentSelector;
    gdt_table[kernelDataSegmentSelectorindex] = dataSegmentSelector;

    gdt_pointer.limit = sizeof(GlobalDescriptorTable::SegmentDescriptor)*GDT_TABLE_SIZE - 1;
    gdt_pointer.base = (uint32_t)gdt_table;
}

void GlobalDescriptorTable::flushGDT(){

    codeSegmentSelectortemp = CodeSegmentSelector();
    dataSegmentSelectortemp = DataSegmentSelector();

    load_gdt((uint32_t)(&gdt_pointer));

    #ifdef DEBUG
	printint(sizeof(GlobalDescriptorTable::SegmentDescriptor));
	print("GDT loaded  ");
	printint((uint32_t)this); print(" Code Segment Selector: ");
	printint(CodeSegmentSelector()); print(" Data Segment Selector: ");
	printint(DataSegmentSelector());
	ln();
    #endif
}

GlobalDescriptorTable::~GlobalDescriptorTable(){}

uint16_t GlobalDescriptorTable::DataSegmentSelector(){

    return (uint8_t*)&gdt_table[kernelDataSegmentSelectorindex] - (uint8_t*)gdt_table;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector(){

    return (uint8_t*)&gdt_table[kernelCodeSegmentSelectorindex] - (uint8_t*)gdt_table;
}

void GlobalDescriptorTable::SegmentDescriptor::setValues(uint32_t base,uint32_t limit,uint8_t flags){

    uint8_t* target = (uint8_t*)this;
    
    if(limit <= 65536){

        target[6] = 0x40;
    }else{

        if((limit & 0xFFF) != 0xFFF)
            limit = (limit >> 12)-1;
        else
            limit = limit >> 12;
        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    target[5] = flags;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base(){

    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];

    return result;
}