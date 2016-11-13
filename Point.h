//
// Created by fsoukup on 16.10.2016.
//

#ifndef QUICKHULL_POINT_H
#define QUICKHULL_POINT_H

#include <iostream>
#include <iomanip>

using namespace std;

struct Point {
public:
    Point() : x(0), y(0) {}
    Point(float x, float y) : x(x), y(y) {}
    float x;
    float y;
    friend ostream& operator<<(ostream& stream, const Point& point) {
        stream << setprecision(16) << point.x << " " << point.y;
        return stream;
    }
};

#endif //QUICKHULL_POINT_H
