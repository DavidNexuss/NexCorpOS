struct CONSOLE_SCREEN{

    unsigned int width;
    unsigned int height;
    unsigned int charpos;
    char* vidptr;
};

extern struct CONSOLE_SCREEN cscreen;
extern void setCharacter(unsigned int pos,char text,char color);
extern void jumpToLine(unsigned int line);
extern void ln();

extern void initstdout(char* vidptr);
extern void print(const char *str,char color);
extern void println(const char *str,char color);
extern void cls();
