#include "hardware/port.h"
#include "hardware/port.h"
#include "types.h"
#include "stdafx.h"

Port8Bit::Port8Bit(uint16_t portNumber){
    m_portNumber = portNumber;
}

Port8Bit::~Port8Bit(){}

void Port8Bit::write(uint8_t data){
    write_port8(m_portNumber,data);
}

uint8_t Port8Bit::read(){
    return read_port8(m_portNumber);
}
//--------------------------------------16BIT
Port16Bit::Port16Bit(uint16_t portNumber){
    m_portNumber = portNumber;
}

Port16Bit::~Port16Bit(){}

void Port16Bit::write(uint16_t data){
    write_port16(m_portNumber,data);
}

uint16_t Port16Bit::read(){
    return read_port16(m_portNumber);
}
//--------------------------------------32BIT

Port32Bit::Port32Bit(uint16_t portNumber){
    m_portNumber = portNumber;
}

Port32Bit::~Port32Bit(){}

void Port32Bit::write(uint32_t data){
    write_port32(m_portNumber,data);
}

uint32_t Port32Bit::read(){
    return read_port32(m_portNumber);
}