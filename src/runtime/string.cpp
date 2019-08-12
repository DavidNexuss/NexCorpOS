#include "stdafx.h"
#include "runtime/string.h"
#include "types.h"

string::string(){

    size = 0;
    buffer = nullptr; 
}

string::string(const char * p){

    int i = 0;
    size = 0;
    const char * t = p;

    while (*p++)
        i++;
    
    buffer = new char[i];
    int j = 0;
    for (j;*t; t++,j++)
    {
        buffer[j] = *t;
    }
    
    size = j;
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

bool operator == (const string &s, const string & t){

    if(s.size != t.size) return false;
    else{
        for (size_t i = 0; i < s.size; i++)
        {
            if(s.buffer[i] != t.buffer[i])
                return false;
        }
        
    }

    return true;
}