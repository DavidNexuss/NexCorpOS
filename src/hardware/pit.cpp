#include "stdafx.h"
#include "hardware/pit.h"
#include "hardware/port.h"
#include "std/stdout.h"
#include "cpu/interrupt.h"

PIT_Manager::PIT_Manager():
channel0_p(CHANNEL_0),
channel1_p(CHANNEL_1),
channel2_p(CHANNEL_2),
channel_command(CHANNEL_COMMAND){}

PIT_Manager::~PIT_Manager(){}

void PIT_Manager::initChannel(uint32_t channelIndex,uint8_t accesMode,uint8_t operatingMode,bool bcdBinary){

    tip_t query = bcdBinary;
    query |= (operatingMode << 1);
    query |= (accesMode << 4);
    query |= (channelIndex << 6);

    if(channelIndex & 0b11 == 1){
        println("Attempt to readback on a initChannel procedure!");
    }
        
    channel_command.write(query);

    #ifdef DEBUG
        print("Initialized pit channel with byte: ");
        printhex(query);
        ln();
    #endif
}

void PIT_Manager::readback(uint8_t channels){

    channel_command.write(0b11 << 5);
}

void PIT_Manager::sleep(uint32_t ms){

    disableInterrupts();
    uint32_t reloadValue = ms * 3579545 / 3000;
    initChannel(0,3,0,0);
    channel0_p.write(reloadValue >> 8);
    channel0_p.write(reloadValue);
    while (channel0_p.read() < 128)
    {
        readback(0);
    }
    enableInterrupts();
    uint32_t val = 255;
    cls();
    while (val > 5){

        printint(val = channel0_p.read());
        channel0_p.read();
        ln();
    }
    

    cls();
}