#include "stdafx.h"
#include "hardware/pit.h"
#include "hardware/port.h"
#include "std/stdout.h"
#include "cpu/interrupt.h"


namespace sys{

    PIT_Manager pit_manager;
}

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

void PIT_Manager::latchCommand(uint8_t channels){

    channel_command.write(channels << 6);
}
void PIT_Manager::readback(uint8_t channels){

    channel_command.write(0b11 << 5);
}

extern "C" {extern void _init_PIT(uint32_t frequency);}

void PIT_Manager::sleep(uint32_t ms){

    if(ms == 0) return;
    
    disableInterrupts();

    uint32_t reloadValue = ms * 3579545 / 3000;
    initChannel(0,3,0,0);
    channel0_p.write(reloadValue);
    channel0_p.write(reloadValue >> 8);
    while (channel0_p.read() < 128)
    {
        readback(0);
    }
    enableInterrupts();
    uint16_t lo = 0;
    uint16_t hi = 0;
    uint16_t readVal = 10000;
    while (readVal > 30){

        latchCommand(0);
        lo = channel0_p.read();
        hi = (channel0_p.read());
        readVal = lo | (hi << 8);
    }
}