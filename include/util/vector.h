#pragma once
#include "types.h"
#include "memory/kmemory.h"


template <class V>

class vector
{
private:
    uint32_t _size;
    uint32_t _capacity;
    uint32_t _initialCapacity;

    V* _buffer;

    void reserve(uint32_t amount);

public:
    vector(uint32_t initialCapacity);
    vector();

    void push_back(const V& object);
    
    inline uint32_t size(){return _size;};
    inline uint32_t capacity(){return _capacity;};

    bool empty();
    void clear();

    void remove(uint32_t index);
    void remove(const V& object);
    bool contains(const V& object);

    V& back();
    V& front();

    V& operator [](uint32_t index);

    ~vector();
};


template<class V>
vector<V>::vector(uint32_t initialCapacity){

    _capacity = initialCapacity > 0 ? initialCapacity : 1;
    _initialCapacity = _capacity; 
    _buffer = new V[_capacity];
    _size = 0;    
}

template<class V>
vector<V>::vector() : vector(0){}

template<class V>
vector<V>::~vector(){

    delete[] _buffer;    
}

template<class V>
void vector<V>::reserve(uint32_t amount){

    if(!kresize(_buffer,amount + _capacity)){

        V* t = new V[amount + _capacity];

        for (size_t i = 0; i < _size; i++)
        {
            t[i] = _buffer[i];
        }
        
        delete[] _buffer;
        _buffer = t;
    } 
    _capacity = amount + _capacity;
    
}
template<class V>
void vector<V>::push_back(const V& object){

    if(!(_capacity > _size))
        reserve(1);
    _buffer[_size++] = object;
}


template<class V>
V& vector<V>::back(){
    return _buffer[_size - 1];
}


template<class V>
V& vector<V>::front(){
    return _buffer[0];
}

template<class V>
bool vector<V>::empty(){
    return _size == 0;
}

template<class V>
V& vector<V>::operator [](uint32_t index){
    return _buffer[index];
}

template<class V>
void vector<V>::clear(){

    if(empty())return;

    _size = 0;
    delete[] _buffer;
    _buffer = new V[_initialCapacity];
    _capacity = _initialCapacity;
}

template<class V>
void vector<V>::remove(uint32_t index){

    if(empty())return;
    
    V* t = new V[_capacity];

    int j = 0;
    for (size_t i = 0; i < _size; i++)
    {
        if(index == i){
            j = 1;
            continue;
        }
        t[i - j] = _buffer[i];
    }
    
    delete [] _buffer;
    _buffer = t;
    _size--;
    
}
template<class V>
void vector<V>::remove(const V& obj){

    if(empty())return;
    
    V* t = new V[_capacity];

    int j = 0;
    for (size_t i = 0; i < _size; i++)
    {
        if(obj == _buffer[i]){
            j = 1;
            continue;
        }
        t[i - j] = _buffer[i];
    }
    
    delete [] _buffer;
    _buffer = t;
    _size--;
    
}

template<class V>
bool vector<V>::contains(const V& object){

    for (size_t i = 0; i < _size; i++)
    {
        if(_buffer[i] == object)return true;
    }
    return false;
}
