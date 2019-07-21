#include "types.h"
#include "port.h"

#define PCI_DATA_PORT 0xCFC
#define PCI_COMMAND_PORT 0xCF8

class PCIController{

    Port32Bit dataPort;
    Port32Bit commandPort;

    public:

        PCIController();
        ~PCIController();

    uint32_t Read(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset);
    void Write(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset,uint32_t value);
    
};