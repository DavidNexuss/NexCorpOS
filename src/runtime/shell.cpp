#include "stdafx.h"
#include "runtime/shell.h"
#include "std/stdout.h"
#include "system.h"

namespace sys{

    CommandDB commandDatabase;
    Shell shell[TTY_COUNT];

    Shell* getCurrentShell(){
        return &shell[getCurrentTTYIndex()];
    }

    void handleShellInput(){
        shell[getCurrentTTYIndex()].handleInput();
    }
}

using namespace sys;

Command::Command(string_t name, void (*_function)(string_t args)){

    _name = name;
    _function = _function; 
}

CommandDB::CommandDB(){}
CommandDB::~CommandDB(){}

Command commands[]{

    Command("help",printHelp)
};

int command_size = 1;

bool CommandDB::hasCommand(string_t name){

    for (size_t i = 0; i < command_size; i++)
    {
        Command c = commands[i];
        if(c._name == name)return true;
    }
    
    return false;   
}

Command* CommandDB::getCommand(string_t name){

    for (size_t i = 0; i < commands.getSize(); i++)
    {
        Command* c = (Command*)commands.at(i);
        if(c->_name == name)return c;
    }
    
    return nullptr;   
}

bool CommandDB::addCommand(string_t name,void (*function)(string_t args)){

        if(hasCommand(name)) return false;
        
        Command* m = new Command(name,function);
        commands.push_back(m);
        return true;
}

int CommandDB::getCommandsCount(){return commands.getSize();}

bool CommandDB::performCommand(string_t name,string_t args){

    Command* command = getCommand(name);
    if(command == 0) return false;
    else command->_function(args);
    return true;
}

void CommandDB::printAllCommands(){

    if(commands.getSize() == 0)
        println("No commands available.");
    for (size_t i = 0; i < commands.getSize(); i++)
    {
        Command* command = (Command*)commands.at(i);
        println(command->_name);
    }
        
}
Shell::Shell(){}

void Shell::Activate(){

    cls();
    welcomeMessage();
    print(">");
    m_cursor_start = getConsoleScreen().charpos;
}
void Shell::welcomeMessage(){

    print("This is the NexCorp OS custom shell. On tty ");
    printint(getCurrentTTYIndex());
    ln();
}

void Shell::handleInput(){


    int c = getConsoleScreen().charpos;
    ln();
    int string_len = c - m_cursor_start;
    
    TTY* tty = getCurrentTTY();
    char string[string_len];

    for (size_t i = 0; i < string_len; i++)
    {
        string[i] = tty->data[(m_cursor_start + i) * 2];
    }
    if(!sys::commandDatabase.performCommand(string,0)){
        print("Command does not exists: ");
        print(string);
        ln();
    };



    print(">");
    m_cursor_start = getConsoleScreen().charpos;
}

void Shell::instantiateShell(int tty_index){

    sys::shell[tty_index].Activate();
}

void printHelp(string_t args){ commandDatabase.printAllCommands();}

void addDebugCommands(){

    commandDatabase.addCommand("help",printHelp);
}
