#pragma once
#include "BTNode.h"
#include <iostream>

template<typename T>
class BinaryTree {
public:
        //CONTRUCTORS
    BinaryTree() {
        root = nullptr;
        srand(time(0));
    }
    ~BinaryTree() {
        deleteTreeRecursive(root);
    }

        //FUNCTIONS
    // RETURNS SIZE OF TREE
    int treeSize() { 
        int size = 0;
        return treeSizeRecursive(size, root);
    }
    // INSERTS NODE TO TREE
    bool insert(T el) {
        return insertRecursive(el, root);
    }
    // SEARCHES IF NODE IS IN TREE
    bool search(T el) {
        return searchRecursive(el, root);
    }
    // DELETES NODE WITH KEY el NO THE TREE
    bool deleteKey(T el) {
        return deleteKeyRecursive(el, root);
    }
    // DELETES TREE
    void deleteTree() {
        deleteTreeRecursive(root);
        root = nullptr;
    }
    // DISPLAYS ALL THE KEYS ON THE TREE
    void display() {
        displayRecursive(root);
        std::cout << std::endl;
    }
    // RETURNS RANDOM KEY
    T* randomKey() { 
        int size = 0;
        treeSizeRecursive(size, root); // check the size, uses reference to size
        if (size == 0)
            return nullptr;
        int randNum = rand() % size; // pick a random number within the size 
        return nodeAtPositionRecursive(randNum, root); //return the node in the position randNum
    }
    // CHECKS IF TREE IS EMPTY
    bool isEmpty() {
        return root == nullptr;
    }
private:
    // FUNCTION THAT COUNTS THE NODES IN TREE IN POST ORDER
    int treeSizeRecursive(int &s, BTNode<T> *node) { 
        if (!node)
            return s;
        s++;
        treeSizeRecursive(s, node->left);
        treeSizeRecursive(s, node->right);
        return s;
    }
    //FUNCTION THAT RETRIVES NODE AT GIVEN LOCATION IN TRAVERSAL ORDER
    T* nodeAtPositionRecursive(int &pos, BTNode<T> *node) { 
        if (!node)
            return nullptr; 
        T* result = nodeAtPositionRecursive(pos, node->left); 
        if (result)
            return result;  
        if (pos == 0)       
            return &node->key; 
        pos--;              
        return nodeAtPositionRecursive(pos, node->right); 
    }
    bool insertRecursive(T el, BTNode<T> *&node) {
        if (!node) {
            node = new(std::nothrow) BTNode<T>(el);
            if (!node)
                return false;
            return true;
        }
        if (el < node->key)
            return insertRecursive(el, node->left);
        if (el > node->key)
            return insertRecursive(el, node->right);
        return false;
    }
    bool searchRecursive(T el, BTNode<T> *node) {
        if (!node)
            return false;
        if (el == node->key)
            return true;
        else if (el < node->key)
            return searchRecursive(el, node->left);
        else  return searchRecursive(el, node->right);
    }
    bool deleteKeyRecursive(T el, BTNode<T> *&node) {
        if (!node)
            return false;
        if (el < node->key)
            return deleteKeyRecursive(el, node->left);
        else if (el > node->key)
            return deleteKeyRecursive(el, node->right);
        else {
            if (!node->left && !node->right) { //no children
                delete node;
                node = nullptr;
                return true;
            }
            else if (!node->right) { //once child
                BTNode<T> *tmp = node->left;
                delete node;
                node = tmp;
                return true;
            }
            else if (!node->left) { //one child
                BTNode<T> *tmp = node->right;
                delete node;
                node = tmp;
                return true;
            }
            else {  //two children
                BTNode<T> *successorParent = node;
                BTNode<T> *successor = node->right;
                while(successor->left) {
                    successorParent = successor;
                    successor = successor->left;
                }
                node->key = successor->key;
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                } else {
                    successorParent->right = successor->right;
                }
                delete successor;
                return true;
            }
        }
    }

    void deleteTreeRecursive(BTNode<T> *node) {
        if (!node)
            return;
        deleteTreeRecursive(node->left);
        deleteTreeRecursive(node->right);
        delete node;
    }
    void displayRecursive(BTNode<T> *node) {
        if (!node)
            return;
        displayRecursive(node->left);
        std::cout << node->key << " ";
        displayRecursive(node->right);
    }
    BTNode<T> *root;
};