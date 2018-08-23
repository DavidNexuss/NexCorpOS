#include "kmemory.h"
#include "stdout.h"

void mem_init(){

  println("Initializing memory...");
  print("Heap Size: ");
  printint(heap_size);
  ln();
  print("Kernel After: ");
  printint(kernel_after);
}
