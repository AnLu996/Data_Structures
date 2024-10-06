#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <string>

#include "Node.h" 

using namespace std;

class RedBlackTree{
    private:
        Node* root;
        Node* NIL;

        void leftRotate(Node* x);
        void rightRotate(Node* x);

        //Insert
        void insertFixUp(Node* z);

        //Search
        Node* searchHelper(Node* node, int data);

        




    public:
        RedBlackTree();

        void insert(int key);

};

#endif // REDBLACKTREE_H