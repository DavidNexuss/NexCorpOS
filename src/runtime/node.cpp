#include "stdafx.h"
#include "runtime/node.h"


Node::Node(void* object,Node* last){

    m_object = object;
    m_last = last;
};