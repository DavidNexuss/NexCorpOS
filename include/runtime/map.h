#pragma once
#include "types.h"


template <class V>
struct map_node{

    uint8_t id;
    map_node* next;
    map_node* child;
    map_node* father;
    V* object;
};

template <class K,class V>
class map
{
private:
    map_node<V>* first;

public:
    map();
    ~map();

    void put(K* str, V* obj,int lenght);
    V* get(K* str,int lenght);
    void printMap();
};
