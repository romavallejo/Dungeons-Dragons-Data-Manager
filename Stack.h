#pragma once
#include <iostream>
#include "Node.h"

template<typename T>
class StackTemplate {
public:
    StackTemplate() {
        top = nullptr;
    }
    ~StackTemplate() {
        clear();
    }

    //metodos
    void clear() {
        Node<T>* tmp;
        while(top != nullptr) {
            tmp = top;
            top = top->next;
            delete tmp;
        }
    }
    void imprimir() {
        for (Node<T>* curr = top; curr != nullptr; curr = curr->next)
            std::cout << curr->info << " ";
        std::cout << std::endl;
    }
    bool push(T el) {
        Node<T>* tmp;
        tmp = new(std::nothrow)  Node<T>(el, top);
        if (tmp) {
            top = tmp;
            return true;
        } return false;
        
    }
    bool pop() {
        if (top) {
            Node<T>* tmp = top;
            top = top -> next;
            delete tmp;
            return true;
        } return false;
    }
    const T* getTop() {
        if (top) {
            return &top->info;
        } return nullptr;
    }
    bool isEmpty() {
        return top == nullptr;
    }
private:
     Node<T>* top;
};