#include "stdafx.h"
#include "system.h"

void sleep(unsigned int t){

    t*= SLEEP;
    while(t--){}
}

System::System(){
    

    keyboard_driver = new KeyboardDriver();
    mouse_driver = new MouseDriver();
    
    driver_manager.addDriver(keyboard_driver);
    driver_manager.addDriver(mouse_driver);

    driver_manager.ActivateAll();

    #ifdef DEBUG
    println("System structure created");
    #endif
}
System::~System(){}