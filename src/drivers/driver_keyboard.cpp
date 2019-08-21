#include "config.h"
#include "drivers/driver_keyboard.h"
#include "std/stdout.h"
#include "runtime/shell.h"
#include "hardware/port.h"
#include "hardware/pic.h"
#include "system.h"

KeyboardDriver::KeyboardDriver(): 
keyboard_data_port(KEYBOARD_DATA_PORT),
keyboard_status_port(KEYBOARD_STATUS_PORT){

}
KeyboardDriver::~KeyboardDriver(){}

void KeyboardDriver::init(){

  sys::init_pic(1);
  write_port8(0x21 , 0xFD);
  println("Keyboard Driver Activated");
}

void KeyboardDriver::unload(){}

void KeyboardDriver::handleInterrupt(){

  unsigned char status;
	char keycode;
	/* write EOI */
	CLEAR_EOI();

	status = keyboard_status_port.read();
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = keyboard_data_port.read();
		if(keycode < 0)
			return;
      
    if(keyboard_map[keycode] == '\b'){

      addCursorPosition(-1);
      setCharacter(getConsoleScreen().charpos,' ',0x07);
	  }else if(keyboard_map[keycode] == '\n'){

      if(isShell()){
        sys::handleShellInput();
      }else{

        ln();
        setCursorPosition(getConsoleScreen().charpos);
    
      }
    
    }else if(keycode == 63){
      
    }else if(keycode >= 0x3B && keycode <= 0x44){
     sys::debug_screen->handleKey(keycode - 0x3B);
    }else if(keycode == 0x48){
      if(isShell()){
        if(sys::last_input)
          print(*sys::last_input);
      }
    }else{
      setCharacter(getConsoleScreen().charpos,keyboard_map[keycode],0x07);
      addCursorPosition(1);
    }

  }
}