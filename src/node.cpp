#include "stdafx.h"
#include "node.h"


Node::Node(void* object,Node* last){

    m_object = object;
    m_last = last;
};