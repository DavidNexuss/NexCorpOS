#pragma once
#include "driver.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_INTERRUPT_NUMBER 1

extern unsigned char keyboard_map[];

class KeyboardDriver : public Driver{

    void init();
    void unload();

    public:

        KeyboardDriver();
        ~KeyboardDriver();

        static void handleInterrupt();
};