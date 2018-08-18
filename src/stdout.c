#include "stdout.h"

struct CONSOLE_SCREEN cscreen = {85,20,0,0};

/*Sets vidptr*/
void initstdout(char* vidptr){
    cscreen.vidptr = vidptr;
}
/*Updates character value and color at a certain position*/
void setCharacter(unsigned int pos,char text,char color){

  unsigned int p = pos*2;

  cscreen.vidptr[p] = text;
  cscreen.vidptr[p + 1] = color;
  cscreen.charpos = pos;
}
/*Sets charposition to the chosen line*/
void jumpToLine(unsigned int line){

  cscreen.charpos = line * cscreen.width;
}
/*Sets charposition to the next line*/
void ln(){

    cscreen.charpos += cscreen.width - (cscreen.charpos % cscreen.width) - 5 * (cscreen.charpos / cscreen.width) - 5;
}

/*Prints to the current charposition*/
void print(const char* str,char color){

  unsigned int i = 0;
  unsigned int j = 0;
  /* this loop writes the string to video memory */
  while(str[j] != '\0') {
    /* the character's ascii */
    setCharacter(cscreen.charpos,str[j],color);
    cscreen.charpos++;
    ++j;
  }
}
/*Same as print but moves charposition to the next line*/
void println(const char* str,char color){

  print(str,color);
  ln();
}
/*Cleans screen*/
void cls(){

  unsigned int j = 0;
  /* this loops clears the screen
	* there are 25 lines each of 80 columns; each element takes 2 bytes */
	while(j < cscreen.width * cscreen.height * 2) {
		/* blank character */
    cscreen.vidptr[j] = ' ';
		/* attribute-byte - light grey on black screen */
		cscreen.vidptr[j+1] = 0x07;
		j = j + 2;

  }
}
