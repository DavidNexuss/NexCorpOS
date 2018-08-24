#include "kmemory.h"
#include "stdout.h"

static void* next_address = &kernel_after;
struct memory_block *last = NULL;

void mem_init(){

  println("Initializing memory...");
  print("Heap Size: ");
  printint(heap_size);
  ln();
  print("Kernel After: ");
  printint(kernel_after);
}

void* kfind_free_block(size_t size){

  struct memory_block *current = last;

  if(last == NULL) return 0;

  struct memory_block *best = NULL;

  while(current){

    if(current->free && current->size >= size && (!best || current->size < best->size)){
      best = current;
      println("NOOO");
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
