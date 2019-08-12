#include "std/stdout.h"
#include "runtime/node.h"

struct Command{
    
    string_t _name;
    void (*_function)(string_t args);

    Command(string_t name, void (*function)(string_t args));
    ~Command();
};

class CommandDB{

    public:
    CommandDB();
    ~CommandDB();


    bool hasCommand(string_t name);
    Command* getCommand(string_t name);
    bool addCommand(string_t name,void (*function)(string_t args));

    int getCommandsCount();
    bool performCommand(string_t name,string_t args);

    void printAllCommands();
};

class Shell{

    int m_cursor_start;

public:

    Shell();

    void Activate();
    void welcomeMessage();
    void handleInput(); // Call when user presses enter

    //TEST COMMANDS
    void getLine();
    void getTTY();

    static void instantiateShell(int tty_index);
};

namespace sys
{
    extern CommandDB commandDatabase;
    extern Shell shell[TTY_COUNT];

    Shell* getCurrentShell();
    void handleShellInput();
} // namespace sys

void addDebugCommands();