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
        void rightRotate(Mode* x);

        //Insert
        void fixInsert(Node* x);




    public:
        RedBlackTree();

        void insert();

};

#endif // REDBLACKTREE_H