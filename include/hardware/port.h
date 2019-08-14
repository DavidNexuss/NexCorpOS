#pragma once
#include "hardware/port.h"
#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif

extern uint8_t read_port8(uint16_t port);
extern void write_port8(uint16_t port, uint8_t data);

extern uint16_t read_port16(uint16_t port);
extern void write_port16(uint16_t port, uint16_t data);

extern uint32_t read_port32(uint16_t port);
extern void write_port32(uint16_t port, uint32_t data);

#define CLEAR_EOI() write_port8(0x20,0x20)

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class Port8Bit{

    uint16_t m_portNumber;
    public:

        uint8_t read();
        void write(uint8_t data);

        Port8Bit(uint16_t portNumber);
        ~Port8Bit();
};

class Port16Bit{

    uint16_t m_portNumber;
    public:

        uint16_t read();
        void write(uint16_t data);

        Port16Bit(uint16_t portNumber);
        ~Port16Bit();
};

class Port32Bit{

    uint16_t m_portNumber;
    public:

        uint32_t read();
        void write(uint32_t data);

        Port32Bit(uint16_t portNumber);
        ~Port32Bit();
};
#endif