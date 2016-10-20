//
// Created by fsoukup on 16.10.2016.
//

#ifndef QUICKHULL_POINT_H
#define QUICKHULL_POINT_H

#include <iostream>

using namespace std;

class Point {
    int x;
    int y;
public:
    Point(int x, int y);
    virtual ~Point();
    int getX() const;
    int getY() const;
    void Print() const;
};


#endif //QUICKHULL_POINT_H
