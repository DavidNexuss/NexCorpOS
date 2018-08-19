#include "color.h"
#include "stdout.h"
/*
*  kernel.c
*/
void kmain(void)
{

	char *vidptr = (char*)0xb8000; 	//video mem begins here.

	/*Initialization*/
  initstdout(vidptr);
	setBackgroundColor(LIGHT_CYAN);
	cls();
	setBackgroundColor(BLACK);
	setColor(LIGHT_RED);
	print("HELLO");

	return;
}
