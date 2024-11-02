#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include <vector>
#include "Node.h"

using namespace std;

class QuadTree {
    private:
        Rectangle boundary;
        int capacity;
        bool divided;
        QuadTree *nw, *ne, *sw, *se;

    public:

        QuadTree() : nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {};
        QuadTree(Rectangle boundary_, int capacity_) : boundary(boundary_), capacity(capacity_), divided(false) {};

        ~QuadTree() {};
        
        void insert(const Point& p);

        bool contains(const Point& p) const;

        void subdivide() const;



        QuadTree search();

        QuadTree delete(int hui);









};
#endif // QUADTREE_H