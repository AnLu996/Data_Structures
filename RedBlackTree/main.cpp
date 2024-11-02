#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <set>

#include "RedBlackTree.h"

using namespace std;
using namespace chrono;

int main()
{
    // .csv file
    ofstream csvFile("comparisons.csv");
    if (!csvFile.is_open()) {
        cerr << "Error al crear el archivo comparisons.csv" << endl;
        return 1;
    }
    csvFile << "Cantidad de Elementos,Comparaciones Promedio\n";
    
    int max_insertions = 10;

    while (max_insertions <= 10000) {
        RedBlackTree rbt;
    
        // Random number generator
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> insertion_distribution(1, max_insertions);

        set<int> inserted_numbers;

        // Insertion
        auto start_insert = high_resolution_clock::now();

        while (inserted_numbers.size() < max_insertions) {
            int random_number = insertion_distribution(generator);
            if (inserted_numbers.find(random_number) == inserted_numbers.end()) {
                rbt.insert(random_number);
                inserted_numbers.insert(random_number);
            }
        }

        auto end_insert = high_resolution_clock::now();

        // Time insertion
        auto duration_insert = duration_cast<duration<double>>(end_insert - start_insert);
        cout << "Tiempo de inserción: " << duration_insert.count() << " segundos" << endl;

        cout << "ELEMENTOS INSERTADOS: " << inserted_numbers.size() << endl;

        /* Recorrido in-order
        cout << "Inorder traversal:" << endl;
        rbt.inorder(); // Salida con los números insertados aleatoriamente
        cout << endl;*/

        // Graphviz's file generator
        rbt.printGraphviz("RedBlackTree.dot");

        // Searching
        auto start_search = high_resolution_clock::now();

        // Distribution searching
        uniform_int_distribution<int> search_distribution(1, max_insertions);

        // 80 searchs
        for (int i = 0; i < 80; i++) {
            int random_number = search_distribution(generator);
            int comparaciones = 0;
            rbt.search(random_number, comparaciones);

            //cout << "Cantidad de comparaciones para " << random_number << ": " << comparaciones << endl;

            // save at CSV
            csvFile << max_insertions << "," << comparaciones << "\n";
        }

        auto end_search = high_resolution_clock::now();

        // Time searching
        auto duration_search = duration_cast<duration<double>>(end_search - start_search);
        cout << "Tiempo de búsqueda: " << duration_search.count() << " segundos" << endl;

        if (max_insertions == 10) {
            max_insertions = 100;
        }
        else {
            max_insertions+=100;
        }

        cout << endl;
    }

    csvFile.close();
    cout << "Archivo CSV generado: comparisons.csv" << endl;

    return 0;
}
