#include "stdafx.h"
#include "types.h"
#include "cpu/cpu.h"
#include "std/stdout.h"

extern uint32_t stack_space;

namespace sys{

    CPUState* savedCPUState;
}
using namespace sys;
void printCurrentCPUState(){

    print("eax: 0x"); printhex(savedCPUState->eax); ln();
    print("ebx: 0x"); printhex(savedCPUState->ebx); ln();
    print("ecx: 0x"); printhex(savedCPUState->ecx); ln();
    print("edx: 0x"); printhex(savedCPUState->edx); ln();
    ln();
    print("iesp: 0x"); printhex(savedCPUState->iesp); ln();
    print("ebp: 0x"); printhex(savedCPUState->ebp); ln();
    print("esi: 0x"); printhex(savedCPUState->esi); ln();
    print("edi: 0x"); printhex(savedCPUState->edi); ln();

    ln();
    print("ds: 0x"); printhex(savedCPUState->ds & 0xFF); ln();
    print("es: 0x"); printhex(savedCPUState->es & 0xFF); ln();
    print("fs: 0x"); printhex(savedCPUState->fs & 0xFF); ln();
    print("gs: 0x"); printhex(savedCPUState->gs & 0xFF); ln();
    ln();

    print("error: 0x"); printhex(savedCPUState->error); ln();
    print("eip: 0x"); printhex(savedCPUState->eip); ln();
    print("cs: 0x"); printhex(savedCPUState->cs); ln();
    print("eflags: 0x"); printhex(savedCPUState->eflags); ln();
    print("esp: 0x"); printhex(savedCPUState->esp); ln();
    print("ss: 0x");printhex(savedCPUState->ss); ln();

    print("stack_space: ");
    printhex((uint32_t)&stack_space);
    ln();
}