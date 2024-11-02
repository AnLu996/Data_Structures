#include <iostream>
#include <unordered_map>
#include <string>

struct Node {
    std::string data;
    Node* next;        

    Node(const std::string& data) : data(data), next(nullptr) {}
};


class Queue {
private:
    Node* head; 
    Node* tail; 

public:
    Queue() : head(nullptr), tail(nullptr) {}

    
    void enqueue(const std::string& data) {
        Node* newNode = new Node(data);
        if (!head) {              
            head = tail = newNode;
        } else {
            tail->next = newNode; 
            tail = newNode;
        }
    }

    std::string dequeue() {
        if (!head) {
            return "";
        }
        Node* temp = head;
        std::string data = head->data;
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
        delete temp;
        return data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Node* getHead() const {
        return head;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

class CacheFIFO {
private:
    Queue queue;
    std::unordered_map<std::string, int> cacheMap;
    int maxSize;
    int currentSize;

public:
    CacheFIFO(int size) : maxSize(size), currentSize(0) {}

    void insertData(const std::string& data) {
        if (cacheMap.find(data) != cacheMap.end()) {
            cacheMap[data]++;
            std::cout << "El dato \"" << data << "\" ya esta en la cache. Llamado: " << cacheMap[data] << " veces.\n";
            return;
        }

        if (currentSize == maxSize) {
            std::string oldest = queue.dequeue();
            cacheMap.erase(oldest);
            currentSize--;
            std::cout << "Se retira el dato \"" << oldest << "\" de la cache.\n";
        }

        queue.enqueue(data);
        cacheMap[data] = 1;
        currentSize++;
        std::cout << "Dato \"" << data << "\" insertado en la cache.\n";
    }

    void printCache() const {
        std::cout << "Estado de la cache: ";
        Node* current = queue.getHead(); 

        while (current) {
            std::cout << "[\"" << current->data << "\"] ";
            current = current->next;
        }
        std::cout << "\n";
    }
};

void showMenu() {
    std::cout << "\n--- MENU DE CACHE USANDO FIFO ---\n";
    std::cout << "1. Insertar\n";
    std::cout << "2. Ver estado\n";
    std::cout << "3. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    CacheFIFO cache(3);  // Tamaño Caché
    int choice;
    std::string input;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Ingrese un string: ";
                std::cin >> input;
                cache.insertData(input);
                break;
            case 2:
                cache.printCache();
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (choice != 3);

    return 0;
}
