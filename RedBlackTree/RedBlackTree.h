#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class RedBlackTree {
    private:
        Node* root;
        Node* NIL;

        void leftRotate(Node* x);
        void rightRotate(Node* x);

        // Insert
        void insertFixUp(Node* z);

        void inorderHelper(Node* node);

        // Search
        Node* searchHelper(Node* node, int data, int& cont);

    public:
        RedBlackTree();

        Node* getRoot() const;
        void insert(int key);
        void inorder();
        Node* search(int data, int& cont);
};

#endif // REDBLACKTREE_H
