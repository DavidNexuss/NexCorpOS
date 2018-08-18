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
	cls();

	jumpToLine(1);
	printTestMessage();
	jumpToLine(0);
	/*Debug Tests*/
	char a = 0x0;
	while(1){

		print("HELLO THIS IS MY AWESOME KERNEL");
		setColor(a++);
		jumpToLine(0);
	}
	return;
}
