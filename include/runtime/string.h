#pragma once

#ifdef __cplusplus

class string
{
private:
    
    int size;
    char *buffer;

public:
    string();
    string(const string &);
    string(const char *);
    ~string();

    int lenght();
    void operator = (const string&);
    operator char*();

    char& operator[] (unsigned int);
    
    bool equals(const string & other);
    char* getBuffer();
    bool operator == (const string &);


};

#endif


#ifdef __cplusplus
extern "C"{
#endif

char* strcpy(char* destination, const char* source);

#ifdef __cplusplus
}
#endif
