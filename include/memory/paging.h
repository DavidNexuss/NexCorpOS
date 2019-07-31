#pragma once
#include "types.h"

typedef uint32_t page_t;

namespace sys{

    void printPageAddresses();
};

extern "C"{

    extern uint32_t page_bottom;
    extern uint32_t page_top;
    extern uint32_t page_start;
    void fillPagingTables4kb(uint32_t address,void* pageDirectoryAddress);
    void enablePageDirectory4kb(void* pageDirectory);
};
extern uint32_t page_directory[1024] __attribute__((aligned(4096)));

class PageManager{
    
    
    page_t* pageTable;
    uint32_t pageTableSize = 1024;
    
    uint32_t page_start_address;

    page_t* getPageTableAddress(uint32_t index);
    void createPageDirectoryEntries();
    page_t* createPageEntries(uint32_t pageIndex,uint32_t baseAddress);
    public:
        PageManager();
        ~PageManager();

};