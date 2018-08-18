#define SWIDTH 80
#define SHEIGHT 25
#define LAST_LINE 24

struct CONSOLE_SCREEN{

    unsigned int charpos;
    char color;
    char* vidptr;
};

extern struct CONSOLE_SCREEN cscreen;
extern void setCharacter(unsigned int pos,char text,char color);
extern void setColor(char color);

extern void jumpToLine(unsigned int line);
extern void ln();

extern void initstdout(char* vidptr);
extern void print(char *str);
extern void println(char *str);
extern void printTestMessage();
extern void cls();

/*Basic functionality of types*/

extern char intToChar(int number);
