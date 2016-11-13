//
// Created by fsoukup on 16.10.2016.
//

#ifndef QUICKHULL_NORMALFORMLINE_H
#define QUICKHULL_NORMALFORMLINE_H


// p : a * x + b * y + c = 0
// A[a1, a2]
// v(p, A) = abs(a * a1 + b * a2 + c) / sqrt(a * a + b * b)

// 1 / sqrt(a * a + b * b) - used a ton
//  => invsqrt = 1 / sqrt(a * a + b * b)

#include "Point.h"
#include <cmath>

using namespace std;

class NormalFormLine {
    float a, b, c;
    Point & A, & B, * X;
    double invsqrt; // invsqrt = 1 / sqrt(a * a + b * b)
    double area(Point &A, Point &B, Point &C) {
        return abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    }
public:
    NormalFormLine(Point &A, Point &B, int dir);
    ~NormalFormLine() {
        delete X;
    };
    int compare(Point &P);
    float getDistance(Point &A);
    void Print() const;
};


#endif //QUICKHULL_NORMALFORMLINE_H
