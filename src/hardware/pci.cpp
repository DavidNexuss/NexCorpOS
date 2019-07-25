#include "stdafx.h"
#include "std/stdout.h"
#include "hardware/pci.h"
#include "runtime/node.h"

#define getID()                         \
(uint32_t)((busNumber << 16)\
|(deviceNumber << 11)\
|(functionNumber << 8)\
|(registerOffset & 0xFC)\
|((uint32_t)0x80000000))

PCIController::PCIController():
commandPort(PCI_COMMAND_PORT),
dataPort(PCI_DATA_PORT)
{

    #ifdef DEBUG
    println("PCI Controller initialized");
    #endif
}

PCIController::~PCIController(){}

PCIDeviceDescriptor::PCIDeviceDescriptor(){}
PCIDeviceDescriptor::~PCIDeviceDescriptor(){}

uint32_t PCIController::Read(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset){

    uint32_t id = getID();
    commandPort.write(id);

    uint32_t result = dataPort.read();
    return result >> (8 * (registerOffset % 4));
}
void PCIController::Write(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber,uint32_t registerOffset,uint32_t value){

    uint32_t id = getID();
    commandPort.write(id);
    dataPort.write(value);

}

bool PCIController::deviceHasFunctions(uint16_t busNumber,uint16_t deviceNumber){

    return Read(busNumber,deviceNumber,0, 0x0E) & (1 << 7);
}

void PCIController::selectDrivers(DriverManager *driverManager){

    LinkedList* list = new LinkedList();
    for (size_t bus = 0; bus < 8; bus++)
    {
        for (size_t device = 0; device < 32; device++)
        {
            size_t numFunctions = deviceHasFunctions(bus,device) ? 8 : 1;
            for (size_t function = 0; function < numFunctions; function++)
            {
                PCIDeviceDescriptor dev =  getDeviceDescriptor(bus,device,function);
                if(dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF)
                    continue;
                list->push_back(new PCIDeviceDescriptor(dev));
            }
            
        }
        
    }
    devices_count = new size_t(list->getSize());
    devices_table = (PCIDeviceDescriptor**)list->getList();
    delete list;
    
    #ifdef DEBUG
    printAllDevices();
    #endif
    
}
void PCIController::printAllDevices(){

    print("Device Count: ");
    printint(*devices_count);
    ln();
    for (size_t i = 0; i < *devices_count; i++)
    {
        print("Device: ");
        printint(devices_table[i]->device);
        print(":");
        printint(devices_table[i]->function);
        print(", vendor: ");
        printhex(devices_table[i]->vendor_id);
        print(", class:");
        printhex(devices_table[i]->class_id);
        print(":");
        printhex(devices_table[i]->subclass_id);
        print(", int: ");
        printhex(devices_table[i]->interrupt);
        ln();
    }
    
}
PCIDeviceDescriptor& PCIController::getDeviceDescriptor(uint32_t n){

    return *devices_table[n];
}

size_t PCIController::getDeviceCount(){
    return *devices_count;
}
PCIDeviceDescriptor PCIController::getDeviceDescriptor(uint16_t busNumber,uint16_t deviceNumber,uint16_t functionNumber){

    PCIDeviceDescriptor result;
    
    result.bus = busNumber;
    result.device = deviceNumber;
    result.function = functionNumber;

    result.vendor_id = Read(busNumber,deviceNumber,functionNumber,VENDOR_ID_OFFSET);
    result.device_id = Read(busNumber,deviceNumber,functionNumber,DEVICE_ID_OFFSET);
    
    result.class_id = Read(busNumber,deviceNumber,functionNumber,CLASS_ID_OFFSET);
    result.subclass_id = Read(busNumber,deviceNumber,functionNumber,SUBCLASS_ID_OFFSET);
    result.interface_id = Read(busNumber,deviceNumber,functionNumber,INTERFACE_ID_OFFSET);
    
    result.revision = Read(busNumber,deviceNumber,functionNumber,RESVISION_OFFSET);
    result.interrupt = Read(busNumber,deviceNumber,functionNumber,INTERRUPT_OFFSET);

    return result;
}
