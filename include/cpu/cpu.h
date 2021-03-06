#pragma once
#include "types.h"

struct CPUState;

namespace sys{

    extern CPUState* savedCPUState;
}
struct CPUState{

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    
    uint32_t iesp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;

    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;

    uint32_t error;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
    
}__attribute__((packed));

void printCurrentCPUState();
void printCPUState(CPUState* state);