#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

struct Rectangle {
    int x, y, w, h;
    vector<Point> points;

    Rectangle(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

    bool contains(const Point& point) const {
        return (point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h);
    }
};

#endif // NODE_H