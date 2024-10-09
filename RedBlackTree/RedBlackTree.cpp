#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
    NIL = new Node(0);
    NIL->color = false; // Negro
    NIL->left = NIL->right = NIL->parent = NIL;
    root = NIL;
}

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == NIL) { // NIL por nullptr
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;

    if (y->right != NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == NIL) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void RedBlackTree::insertFixUp(Node* z) {
    while (z->parent != NIL && z->parent->color == true) { // Mientras el padre sea rojo
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right; // Tío

            if (y->color == true) { // Caso 1
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) { // Caso 2
                    z = z->parent;
                    leftRotate(z);
                }
                // Caso 3
                z->parent->color = false;
                z->parent->parent->color = true;
                rightRotate(z->parent->parent);
            }
        }
        else { // Simétrico
            Node* y = z->parent->parent->left; // Tío

            if (y->color == true) { // Caso 1
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) { // Caso 2
                    z = z->parent;
                    rightRotate(z);
                }
                // Caso 3
                z->parent->color = false;
                z->parent->parent->color = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = false;
}


void RedBlackTree::inorderHelper(Node* node) {
    if (node != NIL) {
        inorderHelper(node->left);
        cout << node->key << " ";
        inorderHelper(node->right);
    }
}

Node* RedBlackTree::searchHelper(Node* node, int data, int& cont) {
    cont++;

    if (node == NIL || node->key == data) {
        return node;
    }

    if (data < node->key) {
        return searchHelper(node->left, data, cont);
    }
    else {
        return searchHelper(node->right, data, cont);
    }
}

void RedBlackTree::insert(int key) {
    // New node
    Node* z = new Node(key);
    z->color = true; // Rojo
    z->left = z->right = z->parent = NIL;

    Node* y = NIL;
    Node* x = root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == NIL) {
        root = z;
    }
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }

    insertFixUp(z);
}

void RedBlackTree::inorder() {
    inorderHelper(root);
    cout << endl;
}

Node* RedBlackTree::search(int data, int& cont) {
    return searchHelper(root, data, cont);
}

// Función para imprimir el árbol en formato Graphviz
void RedBlackTree::printGraphvizHelper(Node* node, std::ofstream& file) {
    if (node != NIL) {
        if (node->color) { // Rojo
            file << "    " << node->key << " [style=filled, fillcolor=red, fontcolor=white];\n";
        }
        else { // Negro
            file << "    " << node->key << " [style=filled, fillcolor=black, fontcolor=white];\n";
        }

        if (node->left != NIL) {
            file << "    " << node->key << " -> " << node->left->key << ";\n";
            printGraphvizHelper(node->left, file);
        }
        if (node->right != NIL) {
            file << "    " << node->key << " -> " << node->right->key << ";\n";
            printGraphvizHelper(node->right, file);
        }
    }
}

void RedBlackTree::printGraphviz(const std::string& filename) {
    std::ofstream graphvizFile(filename);
    if (!graphvizFile.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    graphvizFile << "digraph RedBlackTree {\n";
    graphvizFile << "    node [shape=circle];\n";

    printGraphvizHelper(root, graphvizFile);

    graphvizFile << "}\n";
    graphvizFile.close();

    std::cout << "Archivo Graphviz generado: " << filename << std::endl;
}