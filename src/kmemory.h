#pragma once
#include "types.h"

#define BLOCK_SIZE sizeof(struct memory_block)

struct memory_block{

  bool_t free;
  size_t size;
  struct memory_block* next;

};

void mem_init();

void* kmalloc(size_t size);
void* kfind_free_block(size_t size);
void kfree(void* obj);
size_t allocated(bool_t used);

extern size_t heap_size;
extern byte_t heap_bottom;
extern byte_t heap_top;

extern byte_t kernel_start;
extern byte_t kernel_after;
