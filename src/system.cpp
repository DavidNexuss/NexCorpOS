#include "stdafx.h"
#include "system.h"

void sleep(unsigned int t){

    t*= SLEEP;
    while(t--){}
}

System::System(){

    keyboard_driver = new KeyboardDriver();
    mouse_driver = new MouseDriver();
    
    #ifdef DEBUG
    println("System structure created");
    #endif
}
System::~System(){}

void System::setPICsStatus(bool newStatus){
    m_pics_status = newStatus;
}

bool System::getPICsStatus(){return m_pics_status;}