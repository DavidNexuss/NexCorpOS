#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#include "types.h"
#include "std/color.h"
#define SWIDTH 80
#define TTY_COUNT 8
#define SHEIGHT 25
#define SSIZE SWIDTH*SHEIGHT
#define LAST_LINE 24

struct CONSOLE_SCREEN{

    unsigned int charpos;
    char color;
    char backColor;
};

struct TTY{

    struct CONSOLE_SCREEN consoleScreen;
    char data[80*25*2];
    bool graphicsMode;
    bool shell;
};

struct CONSOLE_SCREEN getConsoleScreen();
struct TTY* getCurrentTTY();
int getCurrentTTYIndex();
bool isShell();

bool loadTTY(int index);
void setCursorPosition(unsigned int pos);
void addCursorPosition(unsigned int pos);

void setCharacter(unsigned int pos,char text,char color);
void setColor(char color);
void setBackgroundColor(char color);

void jumpToLine(unsigned int line);
void ln();

void initstdout(char* vidptr);
void print(const char *str);
void printhex(unsigned int n);
void printint(signed int n);
void printints(unsigned int* ints,size_t size);
void println(const char *str);
void printTestMessage();
void cls();

#ifdef __cplusplus
}
#endif
