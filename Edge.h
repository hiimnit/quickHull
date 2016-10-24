//
// Created by fsoukup on 22.10.2016.
//

#ifndef QUICKHULL_EDGE_H
#define QUICKHULL_EDGE_H

#include "Point.h"

using namespace std;

class Edge {
    Point * a, * b;
public:
    Edge(Point * a, Point * b);
    void Print();
    /*
     * 0 - topright
     * 1 - bottomright
     * 2 - bottomleft
     * 3 - topleft
     */
    int direction() {
        if(a->getX() <= b->getX()) {
            if (a->getY() <= b->getY()) return 0;
            return 1;
        }
        if (a->getY() >= b->getY()) return 2;
        return 3;
    }
};


#endif //QUICKHULL_EDGE_H
