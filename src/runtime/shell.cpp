#include "stdafx.h"
#include "runtime/shell.h"
#include "std/stdout.h"
#include "system.h"
#include "memory/paging.h"

namespace sys{

    Shell shell[TTY_COUNT];
    CommandDB* commandDatabase;
    string* last_input;
    Shell* getCurrentShell(){
        return &shell[getCurrentTTYIndex()];
    }

    void handleShellInput(){
        shell[getCurrentTTYIndex()].handleInput();
    }
}

using namespace sys;

Command::Command(string* name, void (*function)()){

    _name = name;
    _function = function; 
}

CommandDB::CommandDB(){}
CommandDB::~CommandDB(){}

bool CommandDB::hasCommand(string& name){

    for (size_t i = 0; i < commands_list.getSize(); i++)
    {
        
        if(commands_list[i]._name->equals(name))return true;
    }
    
    return false;   
}

Command* CommandDB::getCommand(string& name){

    for (size_t i = 0; i < commands_list.getSize(); i++)
    {
        if(commands_list[i]._name->equals(name))return commands_list.get(i);
    }
    
    return nullptr;   
}

bool CommandDB::addCommand(string* name,void (*function)()){

        if(hasCommand(*name)) return false;
        
        Command* m = new Command(name,function);
        commands_list.add(m);
        return true;
}

int CommandDB::getCommandsCount(){return commands_list.getSize();}

bool CommandDB::performCommand(string& name,string args){

    Command* command = getCommand(name);
    if(command == 0) return false;
    else {

        command->_function();
    };
    return true;
}

void CommandDB::printAllCommands(){

    if(commands_list.getSize() == 0)
        println("No commands_list available.");
    for (size_t i = 0; i < commands_list.getSize(); i++)
    {
        print(commands_list[i]._name->getBuffer());
        if(i + 1 != commands_list.getSize())print(", ");
    }
    ln();
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
        if(last_input){
            delete last_input;
        }
        
        last_input = new string(chars);

        if(!commandDatabase->performCommand(*last_input,0)){
            print("Command does not exists: ");
            print(chars);
            ln();
        };
    };
//    

    print(">");
    m_cursor_start = getConsoleScreen().charpos;
}

void Shell::instantiateShell(int tty_index){

    sys::shell[tty_index].Activate();
}

void printHelp(){

    print("Commands: ");
    commandDatabase->printAllCommands();    
}
void addDebugCommands(){

    commandDatabase->addCommand(new string("help"),printHelp);
    commandDatabase->addCommand(new string("cls"),cls);
    commandDatabase->addCommand(new string("test"),printTestMessage);
    commandDatabase->addCommand(new string("lsmem"),printAllMemoryBlocks);
    commandDatabase->addCommand(new string("memloc"),printPageAddresses);

}

void initCommandDB(){

    commandDatabase = new CommandDB();
}
