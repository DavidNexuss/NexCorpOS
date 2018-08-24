#include "kmemory.h"
#include "stdout.h"

static void* next_address = &kernel_after;
struct memory_block *last;

void mem_init(){

  println("Initializing memory...");
  print("Heap Size: ");
  printint(heap_size);
  ln();
  print("Kernel After: ");
  printint(kernel_after);
}

void* kfind_free_block(size_t size){

  struct memory_block *current = (struct memory_block*) &next_address;
  struct memory_block *best = NULL;

  while(current){

    if(current->free && current->size <= size && (!best || current->size < best->size)){
      best = current;
    }
    current = current->next;
  }

  return best;
}
void* kmalloc(size_t size){

  if(size == NULL) return NULL;

  struct memory_block *block = kfind_free_block(size);

  if(!block){

    block = (struct memory_block*) next_address;
    block->size = size;
    next_address += BLOCK_SIZE + size;
  }

  if(last){

    block->next = last;
  }

  last = block;
  block->free = 0;

  return block + BLOCK_SIZE;
}

void kfree(void* obj){

  struct memory_block *block = obj - BLOCK_SIZE;
  block->free = 1;
}
