#include "stdafx.h"
#include "driver.h"
#include "stdout.h"

Driver::Driver(){}
Driver::~Driver(){}

void Driver::Activate(){


    if(ready) println("Device already started");
    else
    {
        ready = true;
        init();
    }
    
}

void Driver::Stop(){

    ready = false;
    unload();
}

void Driver::Reload(){
    
    if(ready)unload();
    init();
}

bool Driver::Status(){

    return ready;
}