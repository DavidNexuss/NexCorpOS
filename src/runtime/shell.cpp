#include "stdafx.h"
#include "runtime/shell.h"
#include "std/stdout.h"
#include "system.h"


CommandDB* commandDatabase;
namespace sys{

    Shell shell[TTY_COUNT];

    Shell* getCurrentShell(){
        return &shell[getCurrentTTYIndex()];
    }

    void handleShellInput(){
        shell[getCurrentTTYIndex()].handleInput();
    }
}

using namespace sys;

Command::Command(string name, void (*_function)(string args)){

    _name = name;
    _function = _function; 
}

CommandDB::CommandDB(){
    commands_list = new LinkedList();
}
CommandDB::~CommandDB(){

    delete commands_list;
}

bool CommandDB::hasCommand(string name){

    for (size_t i = 0; i < commands_list->getSize(); i++)
    {
        Command* c = (Command*)commands_list->at(i);
        if(c->_name == name)return true;
    }
    
    return false;   
}

Command* CommandDB::getCommand(string name){

    for (size_t i = 0; i < commands_list->getSize(); i++)
    {
        Command* c = (Command*)commands_list->at(i);
        if(c->_name == name)return c;
    }
    
    return nullptr;   
}

bool CommandDB::addCommand(string name,void (*function)(string args)){

        if(hasCommand(name)) return false;
        
        Command* m = new Command(name,function);
        commands_list->push_back(m);
        return true;
}

int CommandDB::getCommandsCount(){return commands_list->getSize();}

bool CommandDB::performCommand(string name,string args){

    Command* command = getCommand(name);
    if(command == 0) return false;
    else command->_function(args);
    return true;
}

void CommandDB::printAllCommands(){

    if(commands_list->getSize() == 0)
        println("No commands_list available.");
    for (size_t i = 0; i < commands_list->getSize(); i++)
    {
        Command* command = (Command*)commands_list->at(i);
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
void printHelp(string args){ commandDatabase->printAllCommands();}

void Shell::handleInput(){

    int c = getConsoleScreen().charpos;
    int string_len = c - m_cursor_start;
    ln();
    if(string_len != 0){
    TTY* tty = getCurrentTTY();
        char chars[string_len + 1];

        for (size_t i = 0; i < string_len; i++)
        {
            chars[i] = tty->data[(m_cursor_start + i) * 2];
        }

        chars[string_len] = '\0';
        if(!commandDatabase->performCommand(string(chars),0)){
            print("Command does not exists: ");
            print(chars);
            ln();

            commandDatabase->addCommand(string("help"),printHelp);
            printHelp(0);
        };
    };
//    

    print(">");
    m_cursor_start = getConsoleScreen().charpos;
}

void Shell::instantiateShell(int tty_index){

    sys::shell[tty_index].Activate();
}


void addDebugCommands(){

    commandDatabase->addCommand(string("help"),printHelp);
}

void initCommandDB(){

    commandDatabase = new CommandDB();
}
