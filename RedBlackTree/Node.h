#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    bool color; // true == Red
    Node* left;
    Node* right;
    Node* parent;

    Node(int key) : key(key), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

#endif // NODE_H