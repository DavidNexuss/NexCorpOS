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
	printint(32);
	print(" HELLO");


	return;
}
