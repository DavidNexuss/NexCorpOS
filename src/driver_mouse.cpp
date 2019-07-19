#include "stdafx.h"
#include "driver_mouse.h"
#include "stdout.h"

MouseDriver::MouseDriver():
commandPort(MOUSE_STATUS_PORT),
dataPort(MOUSE_DATA_PORT){}

MouseDriver::~MouseDriver(){}

void MouseDriver::init(){

    offset = 0;
    buttons = 0;

    commandPort.write(0xA8);
    commandPort.write(0x20);
    uint8_t status = dataPort.read() | 2;
    commandPort.write(0x60);
    dataPort.write(status);

    commandPort.write(0xD4);
    dataPort.write(0xF4);
    dataPort.read();

    write_port(0x2C , 0xFD);
    #ifdef DEBUG
    println("Mouse Driver Activated");
    #endif
}

void MouseDriver::unload(){}

void MouseDriver::handleInterrupt(){

    uint8_t status = commandPort.read();
    if(!(status & 0x20)){
        return;
    }

    buffer[offset] = dataPort.read();
    offset = (offset + 1) % 3;
    if(offset == 0){
        x += buffer[1];
        y -= buffer[2];
    }

    setCursorPosition(SWIDTH*y + x);

}