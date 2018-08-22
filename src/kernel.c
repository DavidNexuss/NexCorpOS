#include "color.h"
#include "stdout.h"
#include "stdlib.h"
#include "mem.h"
#include "interrupt.h"
#include "keyboard.h"
/*
*  kernel.c
*/

void init(char* vidptr){

  /*Initialization*/
	initstdout(vidptr);
	cls();
	println("Console started");
	idt_init();
	kb_init();
	mem_init();
	sleep(1);
	cls();
}
void kmain(void)
{

	char *vidptr = (char*)0xb8000; 	//video mem begins here.
	init(vidptr);
	while(1);
	return;
}
