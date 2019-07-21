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

DriverManager::DriverManager(){}
DriverManager::~DriverManager(){}

void DriverManager::addDriver(Driver* driver){
    drivers[numDrivers] = driver;
    numDrivers++;
}

void DriverManager::ActivateAll(){

    
    for (size_t i = 0; i < numDrivers; i++)
    {
        drivers[i]->Activate();
    }
    
}