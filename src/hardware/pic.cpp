#include "config.h"
#include "hardware/pic.h"
#include "types.h"
#include "hardware/port.h"
#include "std/stdout.h"

void sys::init_pics(){

    /* ICW1 - begin initialization */
	write_port8(0x20 , 0x11);
	write_port8(0xA0 , 0x11);

	#ifdef DEBUG
	println("PICs loaded");
	#endif
}

void sys::init_pic(uint8_t picNumber){

	write_port8(0x20 + picNumber, 0x20);
	write_port8(0xA0 + picNumber, 0x28);

	/* ICW3 - setup cascading */
	write_port8(0x20 + picNumber, 0x00);  
	write_port8(0xA0 + picNumber , 0x00);  

	/* ICW4 - environment info */
	write_port8(0x20 + picNumber, 0x01);
	write_port8(0xA0 + picNumber , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	write_port8(0x20 + picNumber , 0xff);
	write_port8(0xA0 + picNumber, 0xff);
}