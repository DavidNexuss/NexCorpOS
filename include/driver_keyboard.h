#pragma once
#include "driver.h"
#include "interrupt_handler.h"
#include "port.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_INTERRUPT_NUMBER 0x21

extern unsigned char keyboard_map[];

class KeyboardDriver : public Driver{

    void init();
    void unload();

    public:

        Port keyboard_status_port;
        Port keyboard_data_port;
        
        KeyboardDriver();
        ~KeyboardDriver();

        void handleInterrupt();
};