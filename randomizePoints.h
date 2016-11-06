//
// Created by fsoukup on 16.10.2016.
//

#ifndef QUICKHULL_RANDOMIZEPOINTS_H
#define QUICKHULL_RANDOMIZEPOINTS_H


#include <set>
#include <vector>
#include "Point.h"

using namespace std;

class randomizePoints {
    /*
    struct PointPointerCmp
    {
        bool operator()(const Point * lhs, const Point * rhs) const {
            if (lhs->getX() < rhs->getX()) return true;
            else if (lhs->getX() > rhs->getX()) return false;
            return lhs->getY() < rhs->getY();
        }
    };*/
public:
    vector<Point *> * getPoints(int n);
};


#endif //QUICKHULL_RANDOMIZEPOINTS_H
