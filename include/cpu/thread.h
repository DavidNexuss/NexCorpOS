#pragma once
#include "cpu/cpu.h"
#include "cpu/gdt.h"
class Task{

    uint8_t stack[4096];
    CPUState* cpustate;

public: 
    Task(GlobalDescriptorTable* gdt);
    ~Task();
};

class TaskManager{

    Task tasks[256];
    uint32_t tasknum;

    TaskManager();
    ~TaskManager();
};