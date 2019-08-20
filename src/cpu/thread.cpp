#include "cpu/cpu.h"
#include "cpu/thread.h"
#include "system.h"
#include "hardware/pit.h"
#include "runtime/shell.h"

namespace sys{

    TaskManager* task_manager;
}
Task::Task() : Task(0){}
Task::Task(void* entry){

    cpustate.eax = 0;
    cpustate.ebx = 0;
    cpustate.ecx = 0;
    cpustate.edx = 0;

    cpustate.esi = 0;
    cpustate.edi = 0;
    cpustate.ebp = (uint32_t)(stack + 4096 - 1);

    cpustate.eip = (uint32_t)entry;
    cpustate.cs = sys::global_descriptor_table->CodeSegmentSelector();
    cpustate.eflags = 0x202;
    cpustate.esp = (uint32_t)(stack + 4096 - 1 - 4);
    cpustate.ss = 0x10;
    
    *(uint32_t*)cpustate.esp = (uint32_t)killTask;
}

Task::~Task(){
}
TaskManager::TaskManager(){

    #ifdef DEBUG
    println("Created task manager");
    #endif
    currentTask = -1;
}
TaskManager::~TaskManager(){}

bool TaskManager::addTask(Task* task){

    tasks.push_back(task);
    println("Added task to the queue");
    return true;
}

CPUState* TaskManager::schedule(CPUState* cpustate){

    print("Scheduling ");
    printint(currentTask);
    print(" ");
    printint(tasks.size());
    print(" ");
    printint(tasks.empty());

    if(tasks.empty()) return cpustate;

    if(currentTask >= 0){
        tasks[currentTask]->cpustate = *cpustate;
        return cpustate;
    }

    if(++currentTask >= tasks.size())
        currentTask %= tasks.size();

    sys::pit_manager.sleep(200000);
    printCPUState(&tasks[currentTask]->cpustate);
    return &tasks[currentTask]->cpustate;
}