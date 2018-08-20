#include "stdout.h"
#include "color.h"

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
void setBackgroundColor(char col){

  cscreen.backColor = col;
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
    setCharacter(cscreen.charpos,str[j],cscreen.color + (cscreen.backColor << 4));
    cscreen.charpos++;
    ++j;
  }
}

void printint(int a){

    int temp = a*10;
    int count = 0;
    while(temp /= 10){
        count++;
    }

    cscreen.charpos += count - 1;
    int end = cscreen.charpos + 1;
    temp = a*10;

    while(temp /= 10){

      if((temp % 10) == 0) setCharacter(cscreen.charpos,'0',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 1) setCharacter(cscreen.charpos,'1',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 2) setCharacter(cscreen.charpos,'2',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 3) setCharacter(cscreen.charpos,'3',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 4) setCharacter(cscreen.charpos,'4',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 5) setCharacter(cscreen.charpos,'5',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 6) setCharacter(cscreen.charpos,'6',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 7) setCharacter(cscreen.charpos,'7',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 8) setCharacter(cscreen.charpos,'8',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 10) == 9) setCharacter(cscreen.charpos,'9',cscreen.color + (cscreen.backColor << 4));
      cscreen.charpos --;
    }

    cscreen.charpos = end;
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
		cscreen.vidptr[j+1] = cscreen.color + (cscreen.backColor << 4);
		j = j + 2;

  }

  cscreen.charpos = 0;
}

char* val(){

  return "";
}
void printTestMessage(){

  print("Hello! if you are running this means that you...  ");
  setColor(GREEN);
  print("Have succeed in compiling my kernel!");
  setColor(LIGHT_GREY);
  ln();
  print("Wich is cool but remember: ");
  setColor(LIGHT_RED);
  print("Don't install this in your computer");
  jumpToLine(LAST_LINE);
  setColor(DARK_GREY);
  print("If that's your case hee... sry you may need to buy a new computer");
}
/*functionality*/
