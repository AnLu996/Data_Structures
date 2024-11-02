#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class FibonacciHeap;

struct Node {
private:
	Node* prev;
	Node* next;
	Node* child;
	Node* parent;
	int call_times;
	std::string data;
	int degree;
	bool marked;
public:
	friend class FibonacciHeap;
	
	Node* getPrev() const { return prev; }
	Node* getNext() const { return next; }
	Node* getChild() const { return child; }
	Node* getParent() const { return parent; }
	int getCallTimes() const { return call_times; }
	std::string getData() const { return data; }
	bool isMarked() const { return marked; }

	bool hasChildren() const { return child != nullptr; }
	bool hasParent() const { return parent != nullptr; }
};

class FibonacciHeap {
protected:
	Node* heap;

public:
	FibonacciHeap() : heap(nullptr) {}

	virtual ~FibonacciHeap() {
		if (heap) {
			_deleteAll(heap);
		}
	}

	Node* insert(const std::string& data) {
		Node* ret = _singleton(data);
		heap = _merge(heap, ret);
		return ret;
	}

	void merge(FibonacciHeap& other) {
		heap = _merge(heap, other.heap);
		other.heap = _empty();
	}

	bool isEmpty() const {
		return heap == nullptr;
	}

	Node* getMinimum() const {
		return heap;
	}

	Node* removeMinimum() {
		Node* old = heap;
		heap = _removeMinimum(heap);
		return old;
	}

	void decreaseKey(Node* n, int value) {
		heap = _decreaseKey(heap, n, value);
	}

    void increaseKey(Node* n) {
		heap = _increaseKey(heap, n, n->call_times + 1);
	}

	Node* find(int value) {
		return _find(heap, value);
	}

private:
	Node* _empty() {
		return nullptr;
	}

	Node* _singleton(const std::string& data) {
		Node* n = new Node;
		n->call_times = 0;
		n->data = data;
		n->prev = n->next = n;
		n->degree = 0;
		n->marked = false;
		n->child = nullptr;
		n->parent = nullptr;
		return n;
	}

	Node* _merge(Node* a, Node* b) {
		if (a == nullptr) return b;
		if (b == nullptr) return a;
		if (a->call_times > b->call_times) std::swap(a, b);
		Node* an = a->next;
		Node* bp = b->prev;
		a->next = b;
		b->prev = a;
		an->prev = bp;
		bp->next = an;
		return a;
	}

	void _deleteAll(Node* n) {
		if (n != nullptr) {
			Node* c = n;
			do {
				Node* d = c;
				c = c->next;
				_deleteAll(d->child);
				delete d;
			} while (c != n);
		}
	}

	void _addChild(Node* parent, Node* child) {
		child->prev = child->next = child;
		child->parent = parent;
		parent->degree++;
		parent->child = _merge(parent->child, child);
	}

	void _unMarkAndUnParentAll(Node* n) {
		if (n == nullptr) return;
		Node* c = n;
		do {
			c->marked = false;
			c->parent = nullptr;
			c = c->next;
		} while (c != n);
	}

	Node* _removeMinimum(Node* n) {
		_unMarkAndUnParentAll(n->child);
		if (n->next == n) {
			n = n->child;
		} else {
			n->next->prev = n->prev;
			n->prev->next = n->next;
			n = _merge(n->next, n->child);
		}
		if (n == nullptr) return n;
		Node* trees[64] = {nullptr};
		while (true) {
			if (trees[n->degree] != nullptr) {
				Node* t = trees[n->degree];
				if (t == n) break;
				trees[n->degree] = nullptr;
				if (n->call_times < t->call_times) {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					_addChild(n, t);
				} else {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					if (n->next == n) {
						t->next = t->prev = t;
						_addChild(t, n);
						n = t;
					} else {
						n->prev->next = t;
						n->next->prev = t;
						t->next = n->next;
						t->prev = n->prev;
						_addChild(t, n);
						n = t;
					}
				}
				continue;
			} else {
				trees[n->degree] = n;
			}
			n = n->next;
		}
		Node* min = n;
		Node* start = n;
		do {
			if (n->call_times < min->call_times) min = n;
			n = n->next;
		} while (n != start);
		return min;
	}

	Node* _cut(Node* heap, Node* n) {
		if (n->next == n) {
			n->parent->child = nullptr;
		} else {
			n->next->prev = n->prev;
			n->prev->next = n->next;
			n->parent->child = n->next;
		}
		n->next = n->prev = n;
		n->marked = false;
		return _merge(heap, n);
	}

	Node* _decreaseKey(Node* heap, Node* n, int value) {
		if (n->call_times < value) return heap;
		n->call_times = value;
		if (n->parent && n->call_times < n->parent->call_times) {
			heap = _cut(heap, n);
			Node* parent = n->parent;
			n->parent = nullptr;
			while (parent && parent->marked) {
				heap = _cut(heap, parent);
				n = parent;
				parent = n->parent;
				n->parent = nullptr;
			}
			if (parent && parent->parent) parent->marked = true;
		} else if (n->call_times < heap->call_times) {
			heap = n;
		}
		return heap;
	}

    Node* _increaseKey(Node* heap, Node* n, int newValue) {
        if (n->call_times > newValue) {
            return heap;
        }

        n->call_times = newValue;
        if (!n->parent) {
            if (n->call_times > heap->call_times) {
                heap = _removeMinimum(heap);
                heap = _merge(heap, n);
            }
        } else if (n->call_times > n->parent->call_times) {
            Node* parent = n->parent;
            heap = _cut(heap, n);
            n->parent = nullptr;
            heap = _merge(heap, n);
        }
        return heap;
    }

	Node* _find(Node* heap, int value) {
		Node* n = heap;
		if (n == nullptr) return nullptr;
		do {
			if (n->call_times == value) return n;
			Node* ret = _find(n->child, value);
			if (ret) return ret;
			n = n->next;
		} while (n != heap);
		return nullptr;
	}
};

class CacheLFU {
private:
    int maxSize;
    FibonacciHeap heap; 
    std::unordered_map<std::string, Node*> cache;

public:
    CacheLFU(int size) : maxSize(size) {}

    void insertData(const std::string& data) {
        auto it = cache.find(data);
        if (it != cache.end()) {
            heap.increaseKey(it->second);
            std::cout << "El dato \"" << data << "\" ya esta en la cache. Se incrementa en 1 la cantidad de llamadas.\n";
            return;
        }

        if (cache.size() == maxSize) {
            Node* lruNode = heap.removeMinimum(); 
            cache.erase(lruNode->getData()); 
            std::cout << "La cache esta llena. Se elimina \"" << lruNode->getData() << "\".\n";
        }

        Node* newNode = heap.insert(data); 
        cache[data] = newNode;
        std::cout << "Se inserta el dato \"" << data << "\" en la cache.\n";
    }

    void printCache() const {
        std::cout << "Estado de la cache (dato, cantidad de llamadas):\n";
        for (const auto& pair : cache) {
            std::cout << "- (" << pair.second->getData() << ", " << pair.second->getCallTimes() << ")\n";
        }
    }
};

void showMenu() {
    std::cout << "\n--- MENU DE CACHE USANDO LFU ---\n";
    std::cout << "1. Insertar\n";
    std::cout << "2. Ver estado\n";
    std::cout << "3. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    CacheLFU cache(3);  // Tamaño cache
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
