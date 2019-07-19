#pragma once

#include "interrupt.h"
#include "kmemory.h"
#include "driver_keyboard.h"
#include "driver_mouse.h"
#include "gdt.h"
#include "interrupt.h"
#include "vector.h"

#define SLEEP 300000000

void sleep(unsigned int t);

class System{


    bool m_pics_status = false;

    public:
        GlobalDescriptorTable* kernel_globalDescriptorTable;
        InterruptManager* interruptManager;

        KeyboardDriver* keyboard_driver;
        MouseDriver* mouse_driver;
        
        void setPICsStatus(bool newStatus);
        bool getPICsStatus();

        System();
        ~System();

};

static System* g_system;