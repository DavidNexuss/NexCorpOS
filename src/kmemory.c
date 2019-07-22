#include "stdafx.h"
#include "kmemory.h"
#include "stdout.h"

static void* next_address = &kernel_after;
struct memory_block *last = NULL;

size_t execution_timer = 0;

void mem_init(){

  execution_timer += 1;
  #ifdef DEBUG
  println("Initializing memory...");
  print("Heap Size: ");
  printint((heap_size >> 16) & 0xFFFFFFFF);
  
  ln();
  print("Kernel After: ");
  printint(kernel_after);
  print(" Next Address:");
  printint((uint32_t)next_address);
  ln();
  #endif
}

void* kfind_free_block(size_t size){

  struct memory_block *current = last;

  if(last == NULL) return 0;

  struct memory_block *best = NULL;

  while(current){

    if(current->free && current->size >= size && (!best || current->size < best->size)){
      best = current;
    }
    current = current->next;
  }

  return best;
}

void* kmalloczero(size_t size){

  void* ptr = kmalloc(size);
  kmemzero(ptr,size);
  return ptr;
}
void* kmalloc(size_t size){

  if(size == NULL) return NULL;

  struct memory_block *block = kfind_free_block(size);

  if(!block){

    block = (struct memory_block*) next_address;
    block->size = size;
    block->serial = MEMORY_BLOCK_SERIAL;
    next_address += BLOCK_SIZE + size;

    if(last){
      block->next = last;
    }
  }

  last = block;
  block->free = 0;
  return (void*)block + BLOCK_SIZE;
}

void kfree(void* obj){

  struct memory_block *block = (struct memory_block*)(obj - BLOCK_SIZE);
  block->free = 1;
}

void kmemzero(void* position,size_t size){

  kmemset(position,0,size);
}
void kmemset(void* position,char val,size_t size){

  void* end = position + size;
    while (position < end) {
        *(char*)(position) = val;
        position++;
      }
}
void kmemSetZero(void *allocatedObject){

  struct memory_block *block = (struct memory_block*)(allocatedObject - BLOCK_SIZE);
  if(!isMemoryBlock(block)) return;
  kmemzero(allocatedObject,block->size);

}
size_t allocated(bool_t used){

  size_t space = 0;
  struct memory_block *current = last;
  while(current){

    if(used){

        if(!current->free)
          space+= current->size;
    }else space += current->size;
    current = current->next;

  }
  return space;
}
uint32_t blockCount(){

   struct memory_block *it = last;
    uint32_t n = 0;
  while (it != NULL)
  {
      it = it->next;
      n++;
  }
  return n;
}
void printAllMemoryBlocks(){

  struct memory_block *it = last;
  uint32_t n = 0;
  ln();
  println("Kernel memory block debug info:");
  while (it != NULL)
  {
      print("Block address: ");
      printint((uint32_t)it);
      ln();
      print("Block Size: ");
      printint(it->size);
      ln();
      it = it->next;
      n++;
  }

  print("Block count: ");
  printint(n);
  ln();
  
}
