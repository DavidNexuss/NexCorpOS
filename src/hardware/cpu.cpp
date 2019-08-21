#include "config.h"
#include "types.h"
#include "cpu/cpu.h"
#include "std/stdout.h"

extern uint32_t stack_space;

namespace sys{

    CPUState* savedCPUState;
}
using namespace sys;

void printCPUState(CPUState* state){
    print("eax: 0x"); printhex(state->eax); ln();
    print("ebx: 0x"); printhex(state->ebx); ln();
    print("ecx: 0x"); printhex(state->ecx); ln();
    print("edx: 0x"); printhex(state->edx); ln();
    ln();
    print("esp: 0x"); printhex(state->esp); ln();
    print("ebp: 0x"); printhex(state->ebp); ln();
    print("esi: 0x"); printhex(state->esi); ln();
    print("edi: 0x"); printhex(state->edi); ln();

    ln();
    print("ds: 0x"); printhex(state->ds & 0xFF); ln();
    print("es: 0x"); printhex(state->es & 0xFF); ln();
    print("fs: 0x"); printhex(state->fs & 0xFF); ln();
    print("gs: 0x"); printhex(state->gs & 0xFF); ln();
    print("ss: 0x"); printhex(state->ss & 0xFF); ln();
    print("cs: 0x"); printhex(state->cs & 0xFF); ln();
    
    ln();

    print("error: 0x"); printhex(state->error); ln();
    print("eip: 0x"); printhex(state->eip); ln();
    print("eflags: 0x"); printhex(state->eflags); ln();
    print("iesp: 0x"); printhex(state->iesp); ln();
   
    print("stack_space: ");
    printhex((uint32_t)&stack_space);
    ln();
}

void printCurrentCPUState(){

    printCPUState(savedCPUState);
}
