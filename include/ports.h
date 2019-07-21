#ifdef __cplusplus
extern "C"{
#endif
#pragma once
#include "types.h"

extern uint8_t read_port(uint16_t port);
extern void write_port(uint16_t port, uint8_t data);

extern uint16_t read_port16(uint16_t port);
extern void write_port16(uint16_t port, uint16_t data);

extern uint32_t read_port32(uint16_t port);
extern void write_port32(uint16_t port, uint32_t data);

#define CLEAR_EOI() write_port(0x20,0x20)

#ifdef __cplusplus
}
#endif
