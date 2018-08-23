#pragma once
#include "types.h"

void mem_init();

extern size_t heap_size;
extern byte_t heap_bottom;
extern byte_t heap_top;

extern byte_t kernel_start;
extern byte_t kernel_after;
