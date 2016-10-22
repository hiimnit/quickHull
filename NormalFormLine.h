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
    int a;
    int b;
    int c;
    double invsqrt; // invsqrt = 1 / sqrt(a * a + b * b)

public:
    NormalFormLine(Point &A, Point &B);
    /*
     * > 0 -> above
     * < 0 -> under
     * = 0 -> on
     *  --lefttoright Point perspective
     */
    int compare(Point &A);
    double getDistance(Point &A);
    void Print() const;
};


#endif //QUICKHULL_NORMALFORMLINE_H
