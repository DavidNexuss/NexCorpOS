#include "cpu/cpu.h"
#include "cpu/thread.h"
#include "system.h"

Task::Task() : Task(0){}
Task::Task(void* entry){

    stack = new uint8_t[4069]; //4KB
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));

    cpustate->eax = 0;
    cpustate->ebx = 0;
    cpustate->ecx = 0;
    cpustate->edx = 0;

    cpustate->esi = 0;
    cpustate->edi = 0;
    cpustate->ebp = 0;

    cpustate-> eip = (uint32_t)entry;
    cpustate-> cs = sys::global_descriptor_table->CodeSegmentSelector();

    cpustate->eflags = 0x202;
}

Task::~Task(){
    delete[] stack;
}
TaskManager::TaskManager(){
    currentTask = -1;
}
TaskManager::~TaskManager(){}

bool TaskManager::addTask(const Task& task){

    tasks.push_back(task);
    return true;
}

CPUState* TaskManager::schedule(CPUState* cpustate){

    if(tasks.empty()) return cpustate;

    if(currentTask >= 0)
        tasks[currentTask].cpustate = cpustate;
    return 0;

    if(++currentTask >= tasks.size())
        currentTask %= tasks.size();
    return tasks[currentTask].cpustate;
}