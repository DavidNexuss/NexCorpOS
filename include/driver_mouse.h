#pragma once
#include "stdafx.h"
#include "driver.h"
#include "types.h"
#include "port.h"


#define MOUSE_STATUS_PORT 0x64
#define MOUSE_DATA_PORT 0x60
#define MOUSE_INTERRUPT_NUMBER 0x2C

class MouseDriver : public Driver {

    void init();
    void unload();

    Port8Bit dataPort;
    Port8Bit commandPort;
    
    uint8_t buffer[3];
    uint8_t offset;
    uint8_t buttons;

    int8_t x = 0,y = 0;

    public:
        MouseDriver();
        ~MouseDriver();

        void handleInterrupt();
};