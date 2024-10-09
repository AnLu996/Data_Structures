#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <set>
#include <fstream> // Para trabajar con archivos

#include "RedBlackTree.h"

using namespace std;
using namespace std::chrono;

// Método para imprimir el árbol en formato Graphviz
void printGraphviz(Node* root, ofstream& file) {
    if (root == nullptr) return;

    if (root->left != nullptr) {
        file << "    " << root->key << " -> " << root->left->key << ";" << endl;
        printGraphviz(root->left, file);
    }

    if (root->right != nullptr) {
        file << "    " << root->key << " -> " << root->right->key << ";" << endl;
        printGraphviz(root->right, file);
    }
}

int main()
{
    RedBlackTree rbt;
    int max_insertions = 10;

    // Random number generator
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, max_insertions); 

    std::set<int> inserted_numbers;

    // Inserting
    auto start_insert = high_resolution_clock::now();

    for (int i = 0; i < max_insertions; i++) {
        int random_number = distribution(generator);
        if (inserted_numbers.find(random_number) == inserted_numbers.end()) {
            rbt.insert(random_number);
            inserted_numbers.insert(random_number);
        }
    }

    auto end_insert = high_resolution_clock::now();

    // Time insertion
    auto duration_insert = duration_cast<duration<double>>(end_insert - start_insert);
    cout << "Tiempo de insercion: " << duration_insert.count() << " segundos" << endl;

    // Inorder traversal
    cout << "Inorder traversal:" << endl;
    rbt.inorder(); // Salida con los números insertados aleatoriamente
    cout << endl;

    // Graphviz output
    ofstream graphvizFile("RedBlackTree.dot");
    graphvizFile << "digraph RedBlackTree {" << endl;
    graphvizFile << "    node [shape=circle];" << endl;
    
    // Generate Graphviz representation
    printGraphviz(rbt.getRoot(), graphvizFile);

    graphvizFile << "}" << endl;
    graphvizFile.close();

    // Searching
    auto start_search = high_resolution_clock::now();
    
    // CSV file for comparisons
    ofstream csvFile("comparisons.csv");
    csvFile << "Número Buscado,Cantidad de Comparaciones" << endl;

    for (int i = 0; i < 80; i++) {
        int random_number = distribution(generator);
        int cont = 0;
        rbt.search(random_number, cont);
        cout << "Cantidad de comparaciones para " << random_number << ": " << cont << endl;

        // Save to CSV
        csvFile << random_number << "," << cont << endl;
    }

    csvFile.close();
    
    auto end_search = high_resolution_clock::now();

    // Time search
    auto duration_search = duration_cast<duration<double>>(end_search - start_search);
    cout << "Tiempo de busqueda: " << duration_search.count() << " segundos" << endl;

    return 0;
}
