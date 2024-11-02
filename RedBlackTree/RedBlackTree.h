#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <fstream>

#include "Node.h"

class RedBlackTree {
private:
    Node* root;
    Node* NIL;

    void leftRotate(Node* x);
    void rightRotate(Node* x);

    void insertFixUp(Node* z);
    void inorderHelper(Node* node);
    Node* searchHelper(Node* node, int data, int& comparisons);
    void printGraphvizHelper(Node* node, std::ofstream& file);

public:
    RedBlackTree();

    void insert(int key);
    void inorder();
    Node* search(int data, int& comparisons);
    Node* getRoot() const { return root; }

    // Graphviz
    void printGraphviz(const std::string& filename);
};

#endif // REDBLACKTREE_H
