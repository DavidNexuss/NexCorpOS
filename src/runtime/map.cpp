#include "stdafx.h"
#include "runtime/map.h"

template <class K,class V>
map<K,V>::map(){

    first = new map_node<V>();
}

template <class K,class V>
map<K,V>::~map(){

    if(first == 0) return;

    map_node<V>* m = first;
    map_node<V>* next;
    while (m)
    {
        if(m->child){
            m = m->child;
            continue;
        }

        if(m->next){

            map_node<V> n = m->next;
            delete m;
            m = n;
            continue;
        }

        if(m->father){

            map_node<V> n = m->father;
            delete m;
            m = n;
            continue;
        }

    }
    
}

template <class K,class V>
void map<K,V>::printMap(){

    
}


template <class K,class V>
V* map<K,V>::get(K* key,int lenght){

    map_node<V>* m = first;
    for (size_t i = 0; i < lenght; i++)
    {
        while (m)
        {
            if(m->id == key[i]){

                if(i + 1 == lenght){
                    break;
                }
                if(m->child){
                    m = m->child;
                    break;
                }
            }else{
                if(m->next){
                    m = m->next;
                    break;
                }
            }
        }           
    }
    
    return m->object;
    
}
template <class K,class V>
void map<K,V>::put(K* key, V* obj,int lenght){

    map_node<V>* m = first;
    
    map_node<V>* p_father;
    map_node<V>* p_next;
    map_node<V>* p_child;
    
    map_node<V>* t;

    for (size_t i = 0; i < lenght; i++)
    {

        while (m)
        {
            if(m->id == key[i]){

                if(i + 1 == lenght){
                    break;
                }
                if(m->child){
                    m = m->child;
                    break;
                }else{

                    t = new map_node<V>();
                    t->father = m;
                    m->child = t;

                    m = t;
                    m->id = key[i + 1];

                    break;
                }
            }else{
                if(m->next){
                    m = m->next;
                    break;
                }else{

                    t = new map_node<V>();
                    t->father = m->father;
                    m->next = t;
                    m = t;
                    break;
                }
            }
                
        }

                
    }

    m->object = obj;
    
}