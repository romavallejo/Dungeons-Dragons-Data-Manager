#pragma once
#include "DLLNode.h"
#include <iostream>
#include <sstream>

template<typename T>
class DobleLinkedList {
public:
        //CONSTRUCTORS
    DobleLinkedList() {
        head = tail = nullptr;
    }
    ~DobleLinkedList() { 
        clear();
    }
        //FUNCTIONS
    //CLEARS THE LIST
    void clear() {
        while (head) {
            DLLNode<T>* tmp = head;
            head = head->next;
            delete tmp;
        } head = tail = nullptr;
        size = 0;
    }
    //DISPLAYS ALL DATA IN THE LIST
    void display() { 
        for (DLLNode<T>* curr = head; curr != nullptr; curr = curr->next)
            std::cout << curr->data << " ";
        std::cout << "\n";
    }
    //RETURNS DATA OF THE LIST INTO STRINGSTREAM
    std::string toString() const {
        std::stringstream ss;
        for (DLLNode<T>* curr = head; curr != nullptr; curr = curr->next) {
            ss << curr->data << " ";
        }
        return ss.str();
    }
    //O(N) INSERTION, BUT GARANTEES ORDER LIST WHEN ALWAYS USED TO INSERT NEW NODE
    bool addInOrder(T el) { 
        if (!head) {
            DLLNode<T>* tmp = new(std::nothrow) DLLNode<T>(el);
            if (!tmp)
                return false;
            head = tail = tmp;
            size++;
            return true;
        }
        if (el <= head->data)
            return addToHead(el);
        for (DLLNode<T>* curr = head->next; curr != nullptr; curr = curr->next) {
            if (el <= curr->data) {
                DLLNode<T>* tmp = new(std::nothrow) DLLNode<T>(el);
                if (!tmp)
                    return false;
                tmp->next = curr;
                tmp->prev = curr->prev;
                curr->prev->next = tmp;
                curr->prev = tmp;
                size++;
                return true;
            }
        }
        return addToTail(el);
    }
    //INSERTS NODE TO HEAD
    bool addToHead(T el) { 
        DLLNode<T>* tmp = new(std::nothrow) DLLNode<T>(el);
        if (!tmp)
            return false;
        if (!head)
            head = tail = tmp;
        else {
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
        size++;
        return true;
    }
    //INSERTS NODE TO TAIL
    bool addToTail(T el) { 
        DLLNode<T>* tmp = new(std::nothrow) DLLNode<T>(el);
        if (!tmp)
            return false;
        if (!head)
            head = tail = tmp;
        else {
            tail->next = tmp;
            tmp->prev = tail;
            tail = tmp;
        }
        size++;
        return true;
    }
    //INSERTS NODE AT GIVEN POSITION
    bool addAtPosition(T el, int pos) { 
        if (size < 0 || head == nullptr)
            return false;
        DLLNode<T>* tmp = new(std::nothrow) DLLNode<T>(el);
        if (!tmp)
            return false;
        if (head == tail) {
            head = tail = tmp;
        }
        else if (pos == 1) {
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
        else if (pos == size) {
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
        }
        else {
            DLLNode<T> *curr = head, *currPrev;
            for (int i = 1; i < pos; i++) 
                curr = curr->next;
            currPrev = curr->prev;
            currPrev->next = tmp;
            tmp->prev = currPrev;
            curr->prev = tmp;
            tmp->next = curr;
        }
        size++;
        return true;
    }
    //DELETES THE CURR HEAD
    bool deleteHead() { 
        if (!head)
            return false;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr; //supper important to set back to nullptr
        } size--;
        return true;
    }
    //DELETES THE CURR TAIL
    bool deleteTail() { 
        if (!head)
            return false;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr; //supper important to set back to nullptr
        } size--;
        return true;
    }
    // SEARCHES FOR VALUE, IF FOUND DELETES FROM LIST FIRST OCCURANCE
    bool deleteValue(T el) { 
        if (head == nullptr)
            return false;
        DLLNode<T>* curr = head;
        for (curr; curr != nullptr && curr->data != el; curr = curr->next);
        if (!curr)
            return false;
        if(curr->prev == nullptr) 
            return deleteHead();
        else if (curr->next == nullptr) 
            return deleteTail();
        else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            size--;
            return true;
        }
    }
    //SEARCHES IF el IS IN LIST, TRUE IF FOUND
    bool search(T el) { 
        if (!head)
            return false;
        for (DLLNode<T>* curr = head; curr != nullptr;  curr = curr->next)
            if (curr->data == el)
                return true;
        return false;
    }
    //RETURNS SIZE
    int getSize() { 
        return size;
    }
    //CHECKS IF LIST IS EMPTY
    bool isEmpty() { 
        return head == nullptr;
    }
    class iterator {
    public:
        iterator(DLLNode<T>* node) : current(node) {}

        T& operator*() {
            return current->data;  
        }

        iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

    private:
        DLLNode<T>* current;
    };

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

private:
    DLLNode<T> *head, *tail;
    int size;
};