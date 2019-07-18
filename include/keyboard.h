#pragma once
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_INTERRUPT_NUMBER 1

void keyboard_handler();
void kb_init();

extern unsigned char keyboard_map[128];
