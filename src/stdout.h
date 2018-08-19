#define SWIDTH 80
#define SHEIGHT 25
#define SSIZE SWIDTH*SHEIGHT
#define LAST_LINE 24

struct CONSOLE_SCREEN{

    unsigned int charpos;
    char color;
    char backColor;
    char* vidptr;
};

struct CONSOLE_SCREEN cscreen;
void setCharacter(unsigned int pos,char text,char color);
void setColor(char color);
void setBackgroundColor(char color);

void jumpToLine(unsigned int line);
void ln();

void initstdout(char* vidptr);
void print(char *str);
void printint(int n);
void println(char *str);
void printTestMessage();
void cls();
