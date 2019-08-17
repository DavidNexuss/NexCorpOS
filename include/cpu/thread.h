#pragma once
#include "cpu/cpu.h"
#include "cpu/gdt.h"
#include "util/vector.h"

class Task{

    friend class TaskManager;
    uint8_t* stack;
    CPUState* cpustate;

public: 
    Task();
    Task(void* entryPoint);
    ~Task();
};

class TaskManager{

    vector<Task> tasks;
    int currentTask;

    TaskManager();
    ~TaskManager();

    bool addTask(const Task& t);
    CPUState* schedule(CPUState* cpu);
};