#include "types.h"
#include "driver.h"
#include "port.h"

#define PCI_DATA_PORT 0xCFC
#define PCI_COMMAND_PORT 0xCF8

#define VENDOR_ID_OFFSET 0x00
#define DEVICE_ID_OFFSET 0x02
#define CLASS_ID_OFFSET 0x0b
#define SUBCLASS_ID_OFFSET 0x0a
#define INTERFACE_ID_OFFSET 0x9
#define RESVISION_OFFSET 0x08
#define INTERRUPT_OFFSET 0x3c

class PCIDeviceDescriptor{

    public:
        uint32_t portBase;
        uint32_t interrupt;

        uint16_t bus;
        uint16_t device;
        uint16_t function;

        uint16_t vendor_id;
        uint16_t device_id;
        
        uint8_t class_id;
        uint8_t subclass_id;
        uint8_t interface_id;

        uint8_t revision;

        PCIDeviceDescriptor();
        ~PCIDeviceDescriptor();
};

class PCIController{

    Port32Bit dataPort;
    Port32Bit commandPort;

    public:

        PCIController();
        ~PCIController();

    uint32_t Read(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset);
    void Write(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset,uint32_t value);
    bool deviceHasFunctions(uint16_t busNumber,uint16_t deviceNumber);
    
    void selectDrivers(DriverManager *driverManager);
    PCIDeviceDescriptor getDeviceDescriptor(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber);
};