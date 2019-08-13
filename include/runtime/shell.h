#include "std/stdout.h"
#include "util/list.h"

struct Command{
    
    string *_name;
    void (*_function)();

    Command(string* name, void (*function)());
    ~Command();
};

class CommandDB{

    list<Command> commands_list;
    public:
    CommandDB();
    ~CommandDB();


    bool hasCommand(string& name);
    Command* getCommand(string& name);
    bool addCommand(string* name,void (*function)());

    int getCommandsCount();
    bool performCommand(string& name,string args);

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
    extern Shell shell[TTY_COUNT];
    extern CommandDB* commandDatabase;
    extern string* last_input;
    Shell* getCurrentShell();
    void handleShellInput();
} // namespace sys

void addDebugCommands();
void initCommandDB();