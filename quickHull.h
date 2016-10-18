//
// Created by fsoukup on 16.10.2016.
//

#ifndef QUICKHULL_QUICKHULL_H
#define QUICKHULL_QUICKHULL_H


#include <vector>
#include <iostream>
#include "Point.h"
#include "NormalFormLine.h"

using namespace std;

class quickHull {
    vector<Point *> * result;
    // nejspi treba poslat i nfl ?
    void findHull(Point &left, Point &right, vector<Point *> &points /*        */);
public:
    quickHull(vector<Point *> &points);
    ~quickHull();
};


#endif //QUICKHULL_QUICKHULL_H
