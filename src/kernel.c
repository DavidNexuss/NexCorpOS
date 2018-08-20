#include "color.h"
#include "stdout.h"
#include "interrupt.h"
#include "keyboard.h"
/*
*  kernel.c
*/

void kmain(void)
{

	char *vidptr = (char*)0xb8000; 	//video mem begins here.

	/*Initialization*/
  initstdout(vidptr);
	cls();
	println("Console started");
	idt_init();
	init_kb();
	while(1);
	return;
}
