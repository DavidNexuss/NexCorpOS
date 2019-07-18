#define CLEAR_EOI() write_port(0x20,0x20)
namespace sys{

    void init_pics();
};