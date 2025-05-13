#pragma once

template<typename T>
class DLLNode {
public:
    DLLNode() {
        data = T(); next = prev = nullptr;
    }
    DLLNode(T el, DLLNode* n = nullptr, DLLNode* p = nullptr) {
        data = el; next = n; prev = p;
    }
    DLLNode *next, *prev;
    T data;
};