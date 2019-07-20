#include "stdafx.h"
#include "driver_keyboard.h"
#include "stdout.h"
#include "ports.h"
#include "pic.h"
KeyboardDriver::KeyboardDriver():
keyboard_data_port(KEYBOARD_DATA_PORT),
keyboard_status_port(KEYBOARD_STATUS_PORT){

}
KeyboardDriver::~KeyboardDriver(){}

void KeyboardDriver::init(){

  sys::init_pic(1);
  write_port(0x21 , 0xFD);
  println("Keyboard Driver Activated");
}

void KeyboardDriver::unload(){}

void KeyboardDriver::handleInterrupt(){

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
    }else if(keycode == 63){
      cls();
    }else{
      setCharacter(getConsoleScreen().charpos,keyboard_map[keycode],LIGHT_RED + (WHITE << 4));
      addCursorPosition(1);
    }

  }
}