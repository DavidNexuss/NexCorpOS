#pragma once
#include "types.h"
#include "port.h"

#define CHANNEL_0 0x40
#define CHANNEL_1 0x41
#define CHANNEL_2 0x42
#define CHANNEL_COMMAND 0x43

typedef unsigned char tip_t;

/*
PIT command table

Bits         Usage
 6 and 7      Select channel :
                 0 0 = Channel 0
                 0 1 = Channel 1
                 1 0 = Channel 2
                 1 1 = Read-back command (8254 only)
 4 and 5      Access mode :
                 0 0 = Latch count value command
                 0 1 = Access mode: lobyte only
                 1 0 = Access mode: hibyte only
                 1 1 = Access mode: lobyte/hibyte
 1 to 3       Operating mode :
                 0 0 0 = Mode 0 (interrupt on terminal count)
                 0 0 1 = Mode 1 (hardware re-triggerable one-shot)
                 0 1 0 = Mode 2 (rate generator)
                 0 1 1 = Mode 3 (square wave generator)
                 1 0 0 = Mode 4 (software triggered strobe)
                 1 0 1 = Mode 5 (hardware triggered strobe)
                 1 1 0 = Mode 2 (rate generator, same as 010b)
                 1 1 1 = Mode 3 (square wave generator, same as 011b)
 0            BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD

Channel read table

Bit/s        Usage
 7            Output pin state
 6            Null count flags
 4 and 5      Access mode :
                 0 0 = Latch count value command
                 0 1 = Access mode: lobyte only
                 1 0 = Access mode: hibyte only
                 1 1 = Access mode: lobyte/hibyte
 1 to 3       Operating mode :
                 0 0 0 = Mode 0 (interrupt on terminal count)
                 0 0 1 = Mode 1 (hardware re-triggerable one-shot)
                 0 1 0 = Mode 2 (rate generator)
                 0 1 1 = Mode 3 (square wave generator)
                 1 0 0 = Mode 4 (software triggered strobe)
                 1 0 1 = Mode 5 (hardware triggered strobe)
                 1 1 0 = Mode 2 (rate generator, same as 010b)
                 1 1 1 = Mode 3 (square wave generator, same as 011b)
 0            BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD

 */
enum pit_mode{

    mode0 = 0b000, // interrupt on terminal count
    mode1 = 0b001, //hardware re-triggerable
    mode2 = 0b010, //rate generator
    mode3 = 0b011, // square wave generator
    mode4 = 0b100, //software triggered strobe
    mode5 = 0b101 //hardware triggered strobe
};
class PIT_Manager{

    tip_t channel0;
    tip_t channel1;
    tip_t channel2;

    Port8Bit channel0_p;
    Port8Bit channel1_p;
    Port8Bit channel2_p;
    Port8Bit channel_command;


    public:
    
    void initChannel(uint32_t channelIndex,uint8_t accesMode,uint8_t operatingMode,bool bcdBinary);
    void readback(uint8_t channels);
    void latchCommand(uint8_t channels);
    
    tip_t readBackStatus();

        PIT_Manager();
        ~PIT_Manager();
        void sleep(uint32_t ms);
};

namespace sys{

    extern PIT_Manager pit_manager;
}

extern "C" {void flush_irq_0();}