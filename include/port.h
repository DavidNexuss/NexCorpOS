#pragma once
#include "ports.h"
#include "types.h"

class Port{

    uint16_t m_portNumber;
    public:

        uint8_t read();
        void write(uint8_t data);

        Port(uint16_t portNumber);
        ~Port();
};