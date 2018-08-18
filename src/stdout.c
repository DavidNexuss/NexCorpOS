#include "stdout.h"
#include "color.h";

struct CONSOLE_SCREEN cscreen = {};
/*Sets vidptr*/
void initstdout(char* vidptr){
    cscreen.vidptr = vidptr;
    cscreen.color = 0x7;
}
/*Updates character value and color at a certain position*/
void setCharacter(unsigned int pos,char text,char color){

  unsigned int p = pos*2;

  cscreen.vidptr[p] = text;
  cscreen.vidptr[p + 1] = color;
  cscreen.charpos = pos;
}

void setColor(char col){

  cscreen.color = col;
}
/*Sets charposition to the chosen line*/
void jumpToLine(unsigned int line){

  cscreen.charpos = line * SWIDTH;
}
/*Sets charposition to the next line*/
void ln(){

    cscreen.charpos += SWIDTH - (cscreen.charpos % SWIDTH);
}

/*Prints to the current charposition*/
void print(char* str){

  unsigned int i = 0;
  unsigned int j = 0;
  /* this loop writes the string to video memory */
  while(str[j] != '\0') {
    /* the character's ascii */
    setCharacter(cscreen.charpos,str[j],cscreen.color);
    cscreen.charpos++;
    ++j;
  }
}
/*Same as print but moves charposition to the next line*/
void println(char* str){

  print(str);
  ln();
}
/*Cleans screen*/
void cls(){

  unsigned int j = 0;
  /* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	while(j < SWIDTH * SHEIGHT * 2) {
		/* blank character */
    cscreen.vidptr[j] = ' ';
		/* attribute-byte - light grey on black screen */
		cscreen.vidptr[j+1] = 0x07;
		j = j + 2;

  }
}

void printTestMessage(){

  print("Hello! if you are running this means that you...  ");
  setColor(GREEN);
  print("Have succeed in compiling my kernel!");
  setColor(LIGHT_GREY);
  ln();
  print("Wich is cool but remember: ");
  setColor(RED);
  print("Don't install this in your computer");
  jumpToLine(LAST_LINE);
  setColor(DARK_GREY);
  print("If that's your case hee... sry you may need to buy a new computer");
}
/*functionality*/

/*NOT WORKING YET, NOT STACK BUILT, ONLY VOID RETURN TYPE FUNCTIONS POSSIBLE*/
char intToChar(int number){

  int temp = number;
  unsigned int digits;

  while(temp != 0){

    digits ++;
    temp /= 10;
  }

  char text[digits];
  char a = 0x0;
  temp = number;
  unsigned int i = 0;

  while( i != digits){

       temp = number / (10 * i);
       temp %= 10;

       if(temp == 0) a = '0'; else
       if(temp == 1) a = '1'; else
       if(temp == 2) a = '2'; else
       if(temp == 3) a = '3'; else
       if(temp == 4) a = '4'; else
       if(temp == 5) a = '5'; else
       if(temp == 6) a = '6'; else
       if(temp == 7) a = '7'; else
       if(temp == 8) a = '8'; else
       if(temp == 9) a = '9';

       text[digits - 1 - i] = a;
       i++;
  }

  return text;

}
