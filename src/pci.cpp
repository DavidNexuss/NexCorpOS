#include "stdafx.h"
#include "stdout.h"
#include "pci.h"

PCIController::PCIController():
commandPort(PCI_COMMAND_PORT),
dataPort(PCI_DATA_PORT)
{

    #ifdef DEBUG
    println("PCI Controller initialized");
    #endif
}

PCIController::~PCIController(){}
 
uint32_t PCIController::Read(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset){

    uint32_t id = 
    0x1 << 31
    | ((busNumber & 0xFF) << 16)
    | ((deviceNumber & 0x1F) << 11)
    | ((functionNumber & 0x07) << 8)
    | (registerOffset & 0xFC);

    commandPort.write(id);
    uint32_t result = dataPort.read();
    return result;
}
void PCIController::Write(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset,uint32_t value){


    uint32_t id = 
    0x1 << 31
    | ((busNumber & 0xFF) << 16)
    | ((deviceNumber & 0x1F) << 11)
    | ((functionNumber & 0x07) << 8)
    | (registerOffset & 0xFC);
}
    