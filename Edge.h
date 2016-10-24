//
// Created by fsoukup on 22.10.2016.
//

#ifndef QUICKHULL_EDGE_H
#define QUICKHULL_EDGE_H

#include "Point.h"

using namespace std;

class Edge {
    Point & A, & B;
public:
    Edge(Point & A, Point & B);
    void Print();
    /* 0 - topright
     * 1 - bottomright
     * 2 - bottomleft
     * 3 - topleft
     */
    int direction() {
        if(A.getX() <= B.getX()) {
            if (A.getY() <= B.getY()) return 0;
            return 1;
        }
        if (A.getY() >= B.getY()) return 2;
        return 3;
    }
};


#endif //QUICKHULL_EDGE_H
