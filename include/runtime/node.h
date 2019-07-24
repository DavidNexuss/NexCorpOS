#pragma once
#include "types.h"

struct Node{

    void* m_object;
    Node* m_last;

    Node(void* object,Node* last);
    ~Node();
};

class LinkedList{


    Node* m_last = 0;
    uint32_t m_size = 0;
    
    public:
    LinkedList();
    ~LinkedList();

    void* at(uint32_t index);
    void push_back(void* object);

    void* getArray(uint32_t typeSize);
    void** getList();
    
    uint32_t getSize();
};