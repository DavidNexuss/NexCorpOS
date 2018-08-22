#include "stdout.h"
#include "stdlib.h"
#include "mem.h"

void mem_init(){

  println("Initializing memory...");
  print("Heap Size: ");
  printint(heap_size);
  ln();
  print("Kernel After: ");
  printint(kernel_after);
}
