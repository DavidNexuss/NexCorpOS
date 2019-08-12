#include "stdafx.h"
#include "std/stdout.h"
#include "std/stdlib.h"
#include "std/color.h"
#include "hardware/port.h"

struct TTY tty[TTY_COUNT];
struct TTY buffer_tty;
extern void _ZN5Shell16instantiateShellEi(int index);

uint32_t current_tty_index = 0;

char* _vidptr;
/*Sets vidptr*/
void initstdout(char* vidptr){
    _vidptr = vidptr;
    for (size_t i = 0; i < TTY_COUNT; i++)
    {
      tty[i].consoleScreen.color = 0x7;
    }
    
}

struct CONSOLE_SCREEN getConsoleScreen(){
  return tty[current_tty_index].consoleScreen; 
}

struct TTY* getCurrentTTY(){

  return &tty[current_tty_index];
}
int getCurrentTTYIndex(){
  return current_tty_index;
}
void setCursorPosition(unsigned int position){
  if(position < 0) position = 0;
  unsigned short location= position;/* Short is a 16bit type , the formula is used here*/

  //Cursor Low port
  write_port8(0x3D4, 0x0F);//Sending the cursor low byte to the VGA
  write_port8(0x3D5, (unsigned char)(location&0xFF));
             //Cursor
  write_port8(0x3D4, 0x0E);//Sending the cursor high byte to the VGA Controller
  write_port8(0x3D5, (unsigned char )((location>>8)&0xFF)); //Char is a 8bit type

  tty[current_tty_index].consoleScreen.charpos = position;
}

void addCursorPosition(unsigned int position){
  tty[current_tty_index].consoleScreen.charpos += position;
  if(tty[current_tty_index].consoleScreen.charpos < 0) tty[current_tty_index].consoleScreen.charpos = 0;
  if(tty[current_tty_index].consoleScreen.charpos > SWIDTH * SHEIGHT){
    tty[current_tty_index].consoleScreen.charpos = 0;
    cls();
  }
  setCursorPosition(tty[current_tty_index].consoleScreen.charpos);
}

bool isShell(){

  return tty[current_tty_index].shell;
}
bool loadTTY(int index){

  if(current_tty_index == index) return false;
  
  for (size_t i = 0; i < SWIDTH * SHEIGHT * 2; i++)
  {
    _vidptr[i] = tty[index].data[i];

  }
  
 // tty[current_tty_index].consoleScreen = tty[index].consoleScreen;
  current_tty_index = index;
  setCursorPosition(tty[current_tty_index].consoleScreen.charpos);
  
  if(current_tty_index != 0 && !tty[current_tty_index].shell){

    _ZN5Shell16instantiateShellEi(current_tty_index);
    tty[current_tty_index].shell = true;
  }
  return true;
}
/*Updates character value and color at a certain position*/
void setCharacter(unsigned int pos,char text,char color){

  unsigned int p = pos*2;

  _vidptr[p] = text;
  _vidptr[p + 1] = color;

  tty[current_tty_index].data[p] = text;
  tty[current_tty_index].data[p + 1] = color;
  
  setCursorPosition(pos);
}

void setColor(char col){

  tty[current_tty_index].consoleScreen.color = col;
}
void setBackgroundColor(char col){

  tty[current_tty_index].consoleScreen.backColor = col;
}
/*Sets charposition to the chosen line*/
void jumpToLine(unsigned int line){

  setCursorPosition(line * SWIDTH);
}
/*Sets charposition to the next line*/
void ln(){

    setCursorPosition(tty[current_tty_index].consoleScreen.charpos + SWIDTH - (tty[current_tty_index].consoleScreen.charpos % SWIDTH));
}

/*Prints to the current charposition*/
void print(const char* str){

  unsigned int j = 0;
  /* this loop writes the string to video memory */
  while(str[j] != '\0') {
    /* the character's ascii */
    setCharacter(tty[current_tty_index].consoleScreen.charpos,str[j],tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4));
    addCursorPosition(1);
    ++j;
  }
}
void printhex(unsigned int a){

    if(a == 0){

      setCharacter(tty[current_tty_index].consoleScreen.charpos,'0',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4));
      addCursorPosition(1);
      return;
    }

    unsigned int temp = a*16;
    unsigned int count = 0;
    while(temp /= 16){
        count++;
    }
    addCursorPosition(count - 1);
    unsigned int end = tty[current_tty_index].consoleScreen.charpos + 1;
    temp = a*16;

    while(temp /= 16){

      if((temp % 16) == 0) setCharacter(tty[current_tty_index].consoleScreen.charpos,'0',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 1) setCharacter(tty[current_tty_index].consoleScreen.charpos,'1',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 2) setCharacter(tty[current_tty_index].consoleScreen.charpos,'2',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 3) setCharacter(tty[current_tty_index].consoleScreen.charpos,'3',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 4) setCharacter(tty[current_tty_index].consoleScreen.charpos,'4',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 5) setCharacter(tty[current_tty_index].consoleScreen.charpos,'5',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 6) setCharacter(tty[current_tty_index].consoleScreen.charpos,'6',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 7) setCharacter(tty[current_tty_index].consoleScreen.charpos,'7',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 8) setCharacter(tty[current_tty_index].consoleScreen.charpos,'8',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 9) setCharacter(tty[current_tty_index].consoleScreen.charpos,'9',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 10) setCharacter(tty[current_tty_index].consoleScreen.charpos,'A',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 11) setCharacter(tty[current_tty_index].consoleScreen.charpos,'B',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 12) setCharacter(tty[current_tty_index].consoleScreen.charpos,'C',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 13) setCharacter(tty[current_tty_index].consoleScreen.charpos,'D',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 14) setCharacter(tty[current_tty_index].consoleScreen.charpos,'E',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 16) == 15) setCharacter(tty[current_tty_index].consoleScreen.charpos,'F',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4));
      
      addCursorPosition(-1);
    }

    setCursorPosition(end);
}

void printint(unsigned int a){

    if(a == 0){

      setCharacter(tty[current_tty_index].consoleScreen.charpos,'0',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4));
      addCursorPosition(1);
      return;
    }
    unsigned int temp = a*10;
    unsigned int count = 0;
    while(temp /= 10){
        count++;
    }

    addCursorPosition(count - 1);
    unsigned int end = tty[current_tty_index].consoleScreen.charpos + 1;
    temp = a*10;

    while(temp /= 10){

      if((temp % 10) == 0) setCharacter(tty[current_tty_index].consoleScreen.charpos,'0',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 1) setCharacter(tty[current_tty_index].consoleScreen.charpos,'1',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 2) setCharacter(tty[current_tty_index].consoleScreen.charpos,'2',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 3) setCharacter(tty[current_tty_index].consoleScreen.charpos,'3',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 4) setCharacter(tty[current_tty_index].consoleScreen.charpos,'4',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 5) setCharacter(tty[current_tty_index].consoleScreen.charpos,'5',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 6) setCharacter(tty[current_tty_index].consoleScreen.charpos,'6',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 7) setCharacter(tty[current_tty_index].consoleScreen.charpos,'7',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 8) setCharacter(tty[current_tty_index].consoleScreen.charpos,'8',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4)); else
      if((temp % 10) == 9) setCharacter(tty[current_tty_index].consoleScreen.charpos,'9',tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4));
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
    _vidptr[j] = ' ';
    tty[current_tty_index].data[j] = ' ';
		/* attribute-byte - light grey on black screen */
		_vidptr[j+1] = tty[current_tty_index].consoleScreen.color + (tty[current_tty_index].consoleScreen.backColor << 4);
    tty[current_tty_index].data[j + 1] = LIGHT_GREY + (tty[current_tty_index].consoleScreen.backColor <<  4);

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
