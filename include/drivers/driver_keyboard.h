#pragma once
#include "drivers/driver.h"
#include "cpu/interrupt_handler.h"
#include "hardware/port.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_INTERRUPT_NUMBER 0x21

extern unsigned char keyboard_map[];

class KeyboardDriver : public Driver{

    void init();
    void unload();

    public:

        Port8Bit keyboard_status_port;
        Port8Bit keyboard_data_port;
        
        KeyboardDriver();
        ~KeyboardDriver();

        void handleInterrupt();
};