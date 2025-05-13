#pragma once

//THIS CLASS Node IS USED FOR THE STACK
template<typename T>
class Node {
public: 
    Node() {
         info = T(); next = nullptr;
    }
    Node(T i, Node* n = nullptr) {
        info = i; next = n;
    }
    Node* next;
    T info;
};