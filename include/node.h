#pragma once

struct Node{

    void* m_object;
    Node* m_last;

    Node(void* object,Node* last);
};