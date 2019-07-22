#include "types.h"
#define CLEAR_EOI() write_port8(0x20,0x20)

namespace sys{

    void init_pics();
    void init_pic(uint8_t picNumber);
};