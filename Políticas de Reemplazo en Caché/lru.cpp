#include <iostream>
#include <unordered_map>
#include <string>

struct Node {
    std::string data;
    Node* prev;
    Node* next;

    Node(const std::string& data) : data(data), prev(nullptr), next(nullptr) {}
};


class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void moveToHead(Node* node) {
        if (node == head) return; 

        if (node == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;

        if (!tail) tail = node;
    }

    void addNode(Node* node) {
        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;

        if (!tail) tail = node;
    }

    Node* removeTail() {
        if (!tail) return nullptr;
        Node* nodeToRemove = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        return nodeToRemove;
    }

    Node* getHead() const {
        return head;
    }

    Node* getTail() const {
        return tail;
    }
};

class CacheLRU {
private:
    int maxSize;
    DoublyLinkedList list; 
    std::unordered_map<std::string, Node*> cache;

public:
    CacheLRU(int size) : maxSize(size) {}

    void insertData(const std::string& data) {
        auto it = cache.find(data);
        if (it != cache.end()) {
            list.moveToHead(it->second);
            std::cout << "El dato \"" << data << "\" ya esta en la cache. Se mueve al frente.\n";
            return;
        }

        if (cache.size() == maxSize) {
            Node* lruNode = list.removeTail(); 
            cache.erase(lruNode->data); 
            std::cout << "Se retira el dato \"" << lruNode->data << "\" de la cache.\n";
            delete lruNode; 
        }

        Node* newNode = new Node(data);
        list.addNode(newNode);
        cache[data] = newNode;
        std::cout << "Dato \"" << data << "\" insertado en la cache.\n";
    }

    void printCache() const {
        std::cout << "Estado de la cache: ";
        Node* current = list.getHead();
        while (current) {
            std::cout << "[\"" << current->data << "\"] ";
            current = current->next;
        }
        std::cout << "\n";
    }
};

void showMenu() {
    std::cout << "\n--- MENU DE CACHE USANDO LRU ---\n";
    std::cout << "1. Insertar\n";
    std::cout << "2. Ver estado\n";
    std::cout << "3. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    CacheLRU cache(3);  // Tamaño cache
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
