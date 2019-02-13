#pragma once
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

extern void keyboard_handler(void);
void kb_init();

extern unsigned char keyboard_map[128];
