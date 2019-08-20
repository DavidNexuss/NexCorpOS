#pragma once
#include "cpu/cpu.h"
#include "cpu/gdt.h"
#include "util/vector.h"

class Task{

    friend class TaskManager;
    
    uint8_t stack[4096];
    CPUState cpustate;

public: 
    Task();
    Task(void* entryPoint);
    ~Task();
};

class TaskManager{

    vector<Task*> tasks;
    signed int currentTask;

    public:
    TaskManager();
    ~TaskManager();

    bool addTask(Task* t);
    CPUState* schedule(CPUState* cpu);
};

namespace sys{

    extern TaskManager* task_manager;
}

extern "C" {void killTask();}
extern "C" {uint32_t geteip();}
extern "C" {void getStack();}