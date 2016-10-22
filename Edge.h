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
};


#endif //QUICKHULL_EDGE_H
