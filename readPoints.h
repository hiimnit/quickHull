//
// Created by fsoukup on 16.10.2016.
//

#ifndef QUICKHULL_RANDOMIZEPOINTS_H
#define QUICKHULL_RANDOMIZEPOINTS_H


#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Point.h"

using namespace std;

class readPoints {
public:
    vector<Point *> * getPoints(string);
    bool checkPoints(string, vector<Point *> &);
};


#endif //QUICKHULL_RANDOMIZEPOINTS_H
