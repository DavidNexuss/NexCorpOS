#include "stdafx.h"
#include "runtime/node.h"
#include "std/stdout.h"

Node::Node(void* object,Node* last){

    m_object = object;
    m_last = last;
};
Node::~Node(){}

LinkedList::LinkedList(){}
LinkedList::~LinkedList(){

    Node* current = m_last;
    uint32_t i = (m_size - 1);
    while (i--)
    {
        Node* tmp = current->m_last;
        delete current;
        current = tmp;
    }
    
}

void* LinkedList::at(uint32_t index){

    uint32_t i = m_size - (index + 1);
    Node* current = m_last;
    while (i--)
    {
        current = current->m_last;
    }
    return current->m_object;
}

void LinkedList::push_back(void *object){

    m_last = new Node(object,m_last);
    m_size++;
}

void** LinkedList::getList(){

    void** list = new void*[m_size];
    uint32_t index = m_size -1;
    Node* current = m_last;

    while (current != 0)
    {
        list[index] = current->m_object;
        current = current->m_last;
        index--;
    }
    return list;
}
void* LinkedList::getArray(uint32_t typeSize){

    uint8_t* array = new uint8_t[m_size*typeSize];
    uint32_t index = m_size -1;
    Node* current = m_last;
    while (current != 0)
    {
        for (size_t b = 0; b < typeSize; b++)
        {
            array[index*typeSize + b] = ((uint8_t*)current->m_object)[b];
        }

        current = current->m_last;
        index--;
        
    }

    return (void*)array;
    
}

uint32_t LinkedList::getSize(){return m_size;}