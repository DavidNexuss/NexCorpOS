#pragma once
#include "types.h"

class DebugScreen{

        public:
            DebugScreen();
            ~DebugScreen();

        void setHandler(uint32_t index,void (*handler)(),const char* name);
        void handleKey(uint32_t index);
};