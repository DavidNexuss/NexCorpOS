#include "color.h"
#include "stdout.h"
#include "keyboard.h"
#include "port.h"

void init_kb(){
  println("initializing keyboard port");
  write_port(0x21 , 0xFD);
}
void keyboard_handler_main(void) {

	unsigned char status;
	char keycode;

	/* write EOI */
	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;
    setCharacter(cscreen.charpos,keyboard_map[keycode],LIGHT_RED + (WHITE << 4));
    cscreen.charpos++;
	}
}
