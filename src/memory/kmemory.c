#include "stdafx.h"
#include "memory/kmemory.h"
#include "std/stdout.h"

static void* next_address = &heap_bottom;
struct memory_block *last = NULL;

size_t reused = 0;
size_t resized = 0;
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

  last = block;
  }else{
//    print("Finded free block! Demanded: ");
//    printint(size);
//    print(":");
//    printint(block->size);
//    ln();
      reused++;
  }

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

bool kresize(void* allocatedObject,size_t newSize){

  struct memory_block* block = (struct memory_block*)(allocatedObject - BLOCK_SIZE);
  if(block == last){
    block->size = newSize;
    resized++;
    return true;
  }
  return false;
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
  while (it->serial == MEMORY_BLOCK_SERIAL)
  {
      print("Block: "); printint((uint32_t)it);
      print(" ,size: "); printint(it->size);
      print(" ,free: "); print(it->free ? "true" : "false");
      ln();
      it = it->next;
      n++;
  }

  print(" Block count: ");
  printint(n);
  print(" Reused: ");
  printint(reused);
  print(" Resized: ");
  printint(resized);
  ln();
  
}

void printAllFreeMemoryBlocks(){

  struct memory_block *it = last;
  uint32_t n = 0;
  uint32_t m = 0;
  ln();
  println("Kernel memory block debug info:");
  while (it->serial == MEMORY_BLOCK_SERIAL)
  {
      if(it->free){

        print("Block: "); printint((uint32_t)it);
        print(" ,size: "); printint(it->size);
        print(" ,free: "); print(it->free ? "true" : "false");
        ln();
        m++;
      }
      it = it->next;
      n++;
  }

  print("Block count: ");
  printint(n);

  print(" Reused counter: ");
  printint(reused);

  print(" Resized: ");
  printint(resized);
  
  print(" Free: ");
  printint(m);
  ln();
  
}
