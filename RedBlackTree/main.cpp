#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <set>
#include <fstream>

#include "RedBlackTree.h"

using namespace std;
using namespace std::chrono;

int main()
{
    RedBlackTree rbt;
    int max_insertions = 10;

    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> insertion_distribution(1, 100); // Rango ampliado para evitar duplicados

    std::set<int> inserted_numbers;

    // Inserción de elementos aleatorios sin duplicados
    auto start_insert = high_resolution_clock::now();

    while (inserted_numbers.size() < max_insertions) {
        int random_number = insertion_distribution(generator);
        if (inserted_numbers.find(random_number) == inserted_numbers.end()) {
            rbt.insert(random_number);
            inserted_numbers.insert(random_number);
        }
    }

    auto end_insert = high_resolution_clock::now();

    // Calcular el tiempo de inserción en segundos
    auto duration_insert = duration_cast<duration<double>>(end_insert - start_insert);
    cout << "Tiempo de inserción: " << duration_insert.count() << " segundos" << endl;

    // Verificar el número de elementos insertados
    cout << "Número de elementos insertados: " << inserted_numbers.size() << endl;

    // Recorrido in-order
    cout << "Inorder traversal:" << endl;
    rbt.inorder(); // Salida con los números insertados aleatoriamente
    cout << endl;

    // Generar archivo Graphviz
    rbt.printGraphviz("RedBlackTree.dot");

    // Búsqueda de elementos y registro de comparaciones
    auto start_search = high_resolution_clock::now();

    // Archivo CSV para comparaciones
    ofstream csvFile("comparisons.csv");
    if (!csvFile.is_open()) {
        cerr << "Error al crear el archivo comparisons.csv" << endl;
        return 1;
    }
    csvFile << "Número Buscado,Cantidad de Comparaciones\n";

    // Distribución para búsqueda
    std::uniform_int_distribution<int> search_distribution(1, 100); // Mismo rango que inserciones

    // Realizar 80 búsquedas aleatorias
    for (int i = 0; i < 80; i++) {
        int random_number = search_distribution(generator);
        int comparaciones = 0;
        rbt.search(random_number, comparaciones);

        // Imprimir en consola
        cout << "Cantidad de comparaciones para " << random_number << ": " << comparaciones << endl;

        // Guardar en CSV
        csvFile << random_number << "," << comparaciones << "\n";
    }

    csvFile.close();
    cout << "Archivo CSV generado: comparisons.csv" << endl;

    auto end_search = high_resolution_clock::now();

    // Calcular el tiempo de búsqueda en segundos
    auto duration_search = duration_cast<duration<double>>(end_search - start_search);
    cout << "Tiempo de búsqueda: " << duration_search.count() << " segundos" << endl;

    return 0;
}
