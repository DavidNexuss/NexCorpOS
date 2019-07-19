#include "port.h"
#include "ports.h"
#include "types.h"
#include "stdafx.h"

Port::Port(uint16_t portNumber){
    m_portNumber = portNumber;
}

Port::~Port(){}

void Port::write(uint8_t data){
    write_port(m_portNumber,data);
}

uint8_t Port::read(){
    return read_port(m_portNumber);
}

