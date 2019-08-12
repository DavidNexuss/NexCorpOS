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

    char& operator[] (unsigned int);
    
    friend bool operator == (const string &, const string &);
};

#endif


#ifdef __cplusplus
extern "C"{
#endif

char* strcpy(char* destination, const char* source);

#ifdef __cplusplus
}
#endif
