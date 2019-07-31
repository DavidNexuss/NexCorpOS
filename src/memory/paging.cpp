#include "stdafx.h"
#include "memory/paging.h"
#include "memory/kmemory.h"
#include "std/stdout.h"


uint32_t page_directory[1024] __attribute__((aligned(4096)));

void sys::printPageAddresses(){

    print("Head bottom:");
    printhex((uint32_t)&heap_bottom);
    ln();
    print("Heap top:");
    printhex((uint32_t)&heap_top);
    ln();
    print("Heap size:");
    printhex(heap_size);
    ln();
    print("Page Directory start:");
    printhex((uint32_t)&page_bottom);
    ln();
    print("Page Directory top:");
    printhex((uint32_t)&page_top);
    ln();
    print("Page Blocks start:");
    printhex((uint32_t)&page_start);

}

page_t* PageManager::getPageTableAddress(uint32_t index){

    return (page_t*)(page_directory[index] & 0xFFF000);
}
void PageManager::createPageDirectoryEntries(){
    for (size_t i = 0; i < 1024; i++)
    {
        page_directory[i] = 0x00000002;
    }
}

page_t* PageManager::createPageEntries(uint32_t pageTableIndex,uint32_t baseAddress){

    page_t* page_table = (page_t*)(page_start_address + 4096*pageTableIndex);

    for (size_t page_index = 0; page_index < 1024; page_index++)
    {
        page_table[page_index] = baseAddress + 4096*page_index | 0x3;
    }

    page_directory[pageTableIndex] = (uint32_t)page_table | 0x3;
    print("Initialized page at: ");
    printhex(page_directory[pageTableIndex]);
    print(" value:");
    printhex(page_table[0]);
    ln();
    return page_table;
        
}
    

PageManager::PageManager(){

    page_start_address = (uint32_t)&page_start;
    createPageDirectoryEntries();
    createPageEntries(0,0);
    createPageEntries(768,0x100000);
    enablePageDirectory4kb(page_directory);
}

PageManager::~PageManager(){}