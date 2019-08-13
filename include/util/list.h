#pragma once
#include "types.h"

template <class T>
struct list_node{

    T* data;
    list_node<T>* prev;
};

template <class T>
class list{

    list_node<T>* last;

    uint32_t m_size;

    public:
    list(){

        last = new list_node<T>();
        kmemSetZero(last);
        m_size = 0;
    }
    ~list(){

        list_node<T>* m = last;
        while (m)
        {
            if (m->prev)
            {
                list_node<T>* t = m;
                m = m->prev;
                delete t;
            }else{
                delete m;
                m = 0;
            }

        }

    }

    void add(T* obj){

        if(!last->data){
            last->data = obj;
        }else{
            list_node<T>* t = last;

            last = new list_node<T>();
            last->data = obj;
            last->prev = t;
        }

        m_size++;
    }
    
    T* back(){
        return last->data;
    }
    
    T* get(uint32_t index){

        uint32_t i = m_size - (index + 1);
        list_node<T>* t = last;
        while(i--)
        {
            t = t->prev;
        }

        return t->data;

    }

    T& operator [] (uint32_t index){
        return *get(index); 
    }
    
uint32_t getSize(){return m_size;}


};