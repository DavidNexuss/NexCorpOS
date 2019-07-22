#include "stdafx.h"
#include "stdout.h"
#include "stdlib.h"
#include "color.h"
#include "ports.h"

struct CONSOLE_SCREEN cscreen = {};

struct CONSOLE_SCREEN getConsoleScreen(){

  return cscreen;
}
/*Sets vidptr*/
void initstdout(char* vidptr){
    cscreen.vidptr = vidptr;
    cscreen.color = 0x7;
}

void setCursorPosition(unsigned int position){
  if(position < 0) position = 0;
  unsigned short location= position;/* Short is a 16bit type , the formula is used here*/

  //Cursor Low port
  write_port(0x3D4, 0x0F);//Sending the cursor low byte to the VGA
  write_port(0x3D5, (unsigned char)(location&0xFF));
             //Cursor
  write_port(0x3D4, 0x0E);//Sending the cursor high byte to the VGA Controller
  write_port(0x3D5, (unsigned char )((location>>8)&0xFF)); //Char is a 8bit type

  cscreen.charpos = position;
}

void addCursorPosition(unsigned int position){
  cscreen.charpos += position;
  if(cscreen.charpos < 0) cscreen.charpos = 0;
  setCursorPosition(cscreen.charpos);
}
/*Updates character value and color at a certain position*/
void setCharacter(unsigned int pos,char text,char color){

  unsigned int p = pos*2;

  cscreen.vidptr[p] = text;
  cscreen.vidptr[p + 1] = color;
  setCursorPosition(pos);
}

void setColor(char col){

  cscreen.color = col;
}
void setBackgroundColor(char col){

  cscreen.backColor = col;
}
/*Sets charposition to the chosen line*/
void jumpToLine(unsigned int line){

  setCursorPosition(line * SWIDTH);
}
/*Sets charposition to the next line*/
void ln(){

    setCursorPosition(cscreen.charpos + SWIDTH - (cscreen.charpos % SWIDTH));
}

/*Prints to the current charposition*/
void print(const char* str){

  unsigned int i = 0;
  unsigned int j = 0;
  /* this loop writes the string to video memory */
  while(str[j] != '\0') {
    /* the character's ascii */
    setCharacter(cscreen.charpos,str[j],cscreen.color + (cscreen.backColor << 4));
    addCursorPosition(1);
    ++j;
  }
}
void printhex(unsigned int a){

    if(a == 0){

      setCharacter(cscreen.charpos,'0',cscreen.color + (cscreen.backColor << 4));
      addCursorPosition(1);
      return;
    }

    unsigned int temp = a*16;
    unsigned int count = 0;
    while(temp /= 16){
        count++;
    }

    addCursorPosition(count - 1);
    unsigned int end = cscreen.charpos + 1;
    temp = a*16;

    while(temp /= 16){

      if((temp % 16) == 0) setCharacter(cscreen.charpos,'0',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 1) setCharacter(cscreen.charpos,'1',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 2) setCharacter(cscreen.charpos,'2',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 3) setCharacter(cscreen.charpos,'3',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 4) setCharacter(cscreen.charpos,'4',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 5) setCharacter(cscreen.charpos,'5',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 6) setCharacter(cscreen.charpos,'6',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 7) setCharacter(cscreen.charpos,'7',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 8) setCharacter(cscreen.charpos,'8',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 9) setCharacter(cscreen.charpos,'9',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 10) setCharacter(cscreen.charpos,'A',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 11) setCharacter(cscreen.charpos,'B',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 12) setCharacter(cscreen.charpos,'C',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 13) setCharacter(cscreen.charpos,'D',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 14) setCharacter(cscreen.charpos,'E',cscreen.color + (cscreen.backColor << 4)); else
      if((temp % 16) == 15) setCharacter(cscreen.charpos,'F',cscreen.color + (cscreen.backColor << 4));
      
      addCursorPosition(-1);
    }

    setCursorPosition(end);
}

void printint(unsigned int a){

    if(a == 0){

      setCharacter(cscreen.charpos,'0',cscreen.color + (cscreen.backColor << 4));
      addCursorPosition(1);
      return;
    }
    unsigned int temp = a*10;
    unsigned int count = 0;
    while(temp /= 10){
        count++;
    }

    addCursorPosition(count - 1);
    unsigned int end = cscreen.charpos + 1;
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
      addCursorPosition(-1);
    }

    setCursorPosition(end);
}

void printints(unsigned int* ints,size_t size){

  print("{");
  for(size_t i = 0; i < size ; i++){

    printint(ints[i]);
    if(i < size - 1) print(",");
  }
  print("}");
}
/*Same as print but moves charposition to the next line*/
void println(const char* str){

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

  setCursorPosition(0);
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
