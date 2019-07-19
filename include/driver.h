#pragma once
#include "stdout.h"
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