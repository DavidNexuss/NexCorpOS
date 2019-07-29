#include "stdafx.h"
#include "system.h"

#ifdef _ENABLE_GDB_STUB_

extern "C"{

    extern void set_debug_traps();
}

COM_Interface* debug_interface;
void initGDBStub(){

    debug_interface = sys::com_manager->initPort(COM_8BITS_LENGHT,PARITY_NONE,COM_ONE_STOP_BIT);
    set_debug_traps();
}
extern "C" void putDebugChar(uint8_t data){

    debug_interface->send(data);
}	/* write a single character      */
extern "C" int getDebugChar(){

    return debug_interface->receive();
}	/* read and return a single char */
extern "C" void exceptionHandler(int exception_number, void *exception_address){

    sys::interrupt_manager->overrideInterruptGate(exception_number,exception_address);
}	/* assign an exception handler   */
#endif