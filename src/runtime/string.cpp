#include "config.h"
#include "runtime/string.h"
#include "std/stdout.h"

#include "memory/kmemory.h"
#include "types.h"

string::string(){

    size = 0;
    buffer = nullptr; 
}

string::string(const string& other){

    size = other.size;
    buffer = new char[size];
    for (size_t i = 0; i < size; i++)
    {
        buffer[i] = other.buffer[i];
    }
    
}
string::string(const char * p){

    int i = 0;
    size = 0;
    const char * t = p;

    while (*p++)
        i++;
    
    buffer = new char[i + 1];
    kmemSetZero(buffer);
    int j = 0;
    for (j;*t; t++,j++)
    {
        buffer[j] = *t;
    }
    
    size = j + 1;
    buffer[i] = '\0';
} 

string::~string(){

    delete[] buffer;
}

int string::lenght(){
    return size;
}
 
char& string::operator[] (unsigned int x){

    return buffer[x];
}

void string::operator = (const string &s){
    buffer = s.buffer;
}

string::operator char*(){
    return buffer;
}

char* string::getBuffer(){
    return buffer;
}
bool string::equals(const string & t){

    if(size != t.size){
        return false;
    } 
    else{
        for (size_t i = 0; i < size; i++)
        {
            if(buffer[i] != t.buffer[i]){
                return false;
            }
        }
        
    }

    return true;
}
bool string::operator == (const string & t){

    return equals(t);
}