#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {
    private:
        int key;
        bool color; // true == rojo
        Node *parent, *right, *left;

    public:
        Node(int key) {
            this->key = key;
            this->color = true;  
            this->parent = nullptr;  
            this->right = nullptr;
            this->left = nullptr;
        }
};

#endif // NODE_H