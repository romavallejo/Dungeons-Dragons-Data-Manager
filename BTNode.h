#pragma once
#include <ctime>

template<typename T>
class BTNode {
public:
    BTNode() {
        key = T(); left = right = nullptr;
    }
    BTNode(T el , BTNode* l = nullptr, BTNode* r = nullptr) {
        key = el; left = l; right = r;
    }
    BTNode *left, *right;
    T key;
};