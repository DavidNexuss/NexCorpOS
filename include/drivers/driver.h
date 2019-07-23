#pragma once
#include "std/stdout.h"

class Driver{

    bool ready = false;

    virtual void init() {};
    virtual void unload() {};

    public:

        Driver();
        ~Driver();

        void Activate();
        void Stop();
        void Reload();

        bool Status();
};

class DriverManager{

    private:
        Driver* drivers[265];
        int numDrivers = 0;
    public:
        DriverManager();
        ~DriverManager();
        
        void addDriver(Driver*);
        void ActivateAll();
};