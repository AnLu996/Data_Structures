#include "QuadTree.h"

~QuadTree::Quadtree() {
    delete no;
    delete ne;
    delete so;
    delete se;
}
void QuadTree::insert(const Point& p) {
    if (!boundary.contains(point))
        return false;

    if (boundary.points.size() < capacity && !divided) {
        boundary.points.push_back(point);
        return true;
    } else {
        if (!divided) {
            subdivide();
        }
        if (no->insert(point) || ne->insert(point) ||
            so->insert(point) || se->insert(point)) {
            return true;
        }
    }
    return false;
}

bool QuadTree::contains(const Point& p) const {
    return (p.x >= x - width && p.x < x + width &&
            p.y >= y - height && p.y < y + height);
}

void QuadTree::subdivide(QuadTree q) const {
    int x = boundary.x;
    int y = boundary.y;
    int w = boundary.w / 2;
    int h = boundary.h / 2;

    no = new QuadTree(Rectangle(x, y, w, h), capacity);
    ne = new QuadTree(Rectangle(x + w, y, w, h), capacity);
    so = new QuadTree(Rectangle(x, y + h, w, h), capacity);
    se = new QuadTree(Rectangle(x + w, y + h, w, h), capacity);
    divided = true;

    for (const auto& point : boundary.points) {
        insert(point);
    }
    boundary.points.clear();
}
