#include "color.h"
#include "stdout.h"
#include "keyboard.h"
#include "ports.h"

void kb_init(){
  println("initializing keyboard port");
  write_port(0x21 , 0xFD);
}
void keyboard_handler_main(void) {

	unsigned char status;
	char keycode;

	/* write EOI */
	CLEAR_EOI();

	status = read_port(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;
      
    if(keyboard_map[keycode] == '\b'){

      addCursorPosition(-1);
      setCharacter(getConsoleScreen().charpos,' ',0x07);
	  }else if(keyboard_map[keycode] == '\n'){

      ln();
      setCursorPosition(getConsoleScreen().charpos);
    }else{
      setCharacter(getConsoleScreen().charpos,keyboard_map[keycode],LIGHT_RED + (WHITE << 4));
      addCursorPosition(1);
    }

  }

}
