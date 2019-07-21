#include "stdafx.h"
#include "stdout.h"
#include "pci.h"

#define getID(id) 0x1 << 31 \
                    | ((busNumber & 0xFF) << 16) \
                    | ((deviceNumber & 0x1F) << 11) \
                    | ((functionNumber & 0x07) << 8) \
                    | (registerOffset & 0xFC)

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

    uint32_t id = getID(id);
    commandPort.write(id);

    uint32_t result = dataPort.read();
    return result >> (8 * (registerOffset % 4));
}
void PCIController::Write(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset,uint32_t value){

    uint32_t id = getID(id);
    commandPort.write(id);
    dataPort.write(value);

}

bool PCIController::deviceHasFunctions(uint16_t busNumber,uint16_t deviceNumber){

    return Read(busNumber,deviceNumber,0, 0x0E) & (1 << 7);
}
    