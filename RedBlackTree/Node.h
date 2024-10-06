#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    bool color; // true == rojo
    Node *parent, *right, *left;

    Node(int key) {
        this->key = key;
        this->color = true;  
        this->parent = nullptr;  
        this->right = nullptr;
        this->left = nullptr;
    }
};

#endif // NODE_H