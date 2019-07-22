#pragma once
#ifdef __cplusplus
extern "C"{
#endif

#include "types.h"

#define BLOCK_SIZE sizeof(struct memory_block)
#define MEMORY_BLOCK_SERIAL 45632
#define isMemoryBlock(block) block->serial == MEMORY_BLOCK_SERIAL

struct memory_block{

  unsigned short serial;
  bool_t free;
  size_t size;
  struct memory_block* next;

};

void mem_init();

void* kmalloc(size_t size);
void* kmalloczero(size_t size);
void* kfind_free_block(size_t size);
void kfree(void* obj);

void kmemzero(void* position,size_t size);
void kmemset(void* position,char val,size_t size);
void kmemSetZero(void* allocatedObject);
uint32_t blockCount();

void printAllMemoryBlocks();
size_t allocated(bool_t used);

extern size_t heap_size;
extern byte_t heap_bottom;
extern byte_t heap_top;

extern byte_t kernel_start;
extern uint32_t kernel_after;

extern size_t execution_timer;

#ifdef __cplusplus
}
#endif