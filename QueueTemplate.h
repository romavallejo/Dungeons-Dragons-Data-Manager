#pragma once
#include <iostream>
#include "Node.h"

template<typename T>
class QueueTemplate {
public: 
    QueueTemplate() {
        front = rear = nullptr;
    }
    ~QueueTemplate() {
        clear();
    }

    //FUNCTIONS
    void clear() {
        while (front) {
            Node<T>* tmp = front;
            front = front->next;
            delete tmp;
        } front = rear = nullptr;
    }
    void imprimir() {
        for (Node<T>* curr = front; curr != nullptr; curr = curr->next)
            std::cout << curr->info << " ";
        std::cout << "\n";
    }
    bool enqueue(T el) {
        Node<T>* tmp = new(std::nothrow) Node<T>(el);
        if (!tmp) return false;
        if (!front) {  
            front = rear = tmp;
        } else {  
            rear->next = tmp;
            rear = tmp;
        }
        return true;
    }
    bool dequeue() {
        if (!front)
            return false;
        Node<T>* tmp = front;
        front = front->next;
        delete tmp;
        if (!front)
            rear = nullptr;
        return true;
    }
    const T* getFront() {
        if (front)
            return &front->info;
        return nullptr;
    }
    bool isEmpty() {
        return front == nullptr;
    }
    bool enqueueFront(T el) {
        Node<T>* tmp = new(std::nothrow) Node<T>(el, front);
        if (!tmp) 
            return false;
        front = tmp;
        return true;
    }
private:
    Node<T> *front, *rear;
};