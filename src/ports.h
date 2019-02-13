#pragma once
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);

#define CLEAR_EOI() write_port(0x20,0x20)
