#pragma once
#include "types.h"
#include "port.h"

#define COM13 0x3F8
#define COM24 0x2F8

#define COM_5BITS_LENGHT 0
#define COM_6BITS_LENGHT 1
#define COM_7BITS_LENGHT 2
#define COM_8BITS_LENGHT 3

#define COM_ONE_STOP_BIT 0
#define COM_TWO_STOP_BITS 1

#define PARITY_NONE 0
#define PARITY_ODD 1
#define PARITY_EVEN 3
#define PARITY_MARK 5
#define PARITY_SPACE 7

struct COMPort{

  //  uint8_t dataRegister; // least significant byte of the divisor value for setting the baud rate
  //  uint8_t interruptEnableRegister;// most significant byte of the divior value
    uint16_t portNumber;
    uint8_t loDivisor; //most significant byte of divisor
    uint8_t hiDivisor; //least significant byte of divisor
   
    uint8_t fifoControlRegisters;
    uint8_t lineControlRegister;
    uint8_t modemControlRegister;
    uint8_t lineStatusRegister;
    uint8_t modemStatusRegister;
    uint8_t scratchRegister;

}__attribute__((packed));

class COM_Interface{

    COMPort comPort;
    uint16_t portNumber;

    void enableDLAB(bool enable);
    bool serialRecieved();
    bool isTransmitEmpty();
    public:
        COM_Interface(COMPort* definition);
        ~COM_Interface();
        void flushConfiguration();

        void send(uint8_t data);
        uint8_t receive();

};
class COM_Manager{

    COM_Interface* coms[4];
    size_t n;

    public:
        COM_Manager();
        ~COM_Manager();
        bool areComsAvaible();
        COM_Interface* getPort(uint32_t index);
        COM_Interface* initPort(uint8_t dataBits,uint8_t parity,bool stopBit);
};