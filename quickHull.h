//
// Created by fsoukup on 16.10.2016.
//

#ifndef QUICKHULL_QUICKHULL_H
#define QUICKHULL_QUICKHULL_H


#include <vector>
#include <iostream>
#include "Point.h"
#include "NormalFormLine.h"
#include "Edge.h"

using namespace std;

class quickHull {
    vector<Edge *> * result;
    vector<Point *> & points;

    void findHull(Point &left, Point &right, vector<Point *> &points, NormalFormLine &nfl, int x);
public:
    quickHull(vector<Point *> &p);
    vector<Edge *> & run();
    ~quickHull();
};


#endif //QUICKHULL_QUICKHULL_H
