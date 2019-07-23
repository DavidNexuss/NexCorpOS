#pragma once
#include "hardware/ports.h"
#include "types.h"

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