#pragma once
extern uint8_t read_port(uint16_t port);
extern void write_port(uint16_t port, uint8_t data);

#define CLEAR_EOI() write_port(0x20,0x20)
