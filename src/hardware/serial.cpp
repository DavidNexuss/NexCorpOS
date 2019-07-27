#include "stdafx.h"
#include "std/stdout.h"
#include "hardware/serial.h"
#include "hardware/port.h"

COM_Interface::COM_Interface(COMPort *definition){

    comPort = *definition;

    portNumber = comPort.portNumber;

    comPort.hiDivisor = 0x00;
    comPort.loDivisor = 0x03;
    comPort.fifoControlRegisters = 0xC7;
    comPort.modemControlRegister = 0x0B;

    flushConfiguration();

    #ifdef DEBUG
    print("COM initialized in: ");
    printhex(portNumber);
    ln();
    #endif
}

COM_Interface::~COM_Interface(){}
void COM_Interface::enableDLAB(bool enable){

    if(enable)
        write_port8(portNumber + 3,0x80);
    else
        write_port8(portNumber + 3,comPort.lineControlRegister);
}
void COM_Interface::flushConfiguration(){

    write_port8(portNumber + 1,0x00);
    enableDLAB(true);
        write_port8(portNumber,comPort.loDivisor);
        write_port8(portNumber + 1,comPort.hiDivisor);
    enableDLAB(false);
    write_port8(portNumber + 2,comPort.fifoControlRegisters);
    write_port8(portNumber + 4, comPort.modemControlRegister);

}

bool COM_Interface::serialRecieved(){

    return (read_port8(portNumber + 5) & 1) != 0; 
}

bool COM_Interface::isTransmitEmpty(){

    return (read_port8(portNumber + 5) & 0x20) != 0;
}
uint8_t COM_Interface::receive(){

    while (!serialRecieved());

    return read_port8(portNumber);
    
}

void COM_Interface::send(uint8_t data){

    while(!isTransmitEmpty());

    write_port8(portNumber,data);
}

COM_Manager::COM_Manager(){
    n = 0;
}
COM_Manager::~COM_Manager(){}


bool COM_Manager::areComsAvaible(){
    return 3 - n > 0;
}

COM_Interface* COM_Manager::getPort(uint32_t index){
    return coms[index];
}

COM_Interface* COM_Manager::initPort(uint8_t dataBits,uint8_t parity,bool stopBit){

    if(!areComsAvaible()) return 0;
    COMPort definition;
    definition.lineControlRegister = 0;
    definition.portNumber = n % 2 == 1 ? COM24:COM13;
    definition.lineControlRegister |= dataBits;
    definition.lineControlRegister |= stopBit << 2;
    definition.lineControlRegister |= parity << 3;
    return coms[++n] = new COM_Interface(&definition);
    
}