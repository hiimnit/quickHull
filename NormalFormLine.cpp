//
// Created by fsoukup on 16.10.2016.
//

#include "NormalFormLine.h"

NormalFormLine::NormalFormLine(Point &A, Point &B) {
    // normal vector = vector + swap
    this->a = (B.getY() - A.getY()) * -1;
    this->b = B.getX() - A.getX();

    this->invsqrt = 1 / sqrt(a * a + b * b); // save -> zbytecne by se opakoval

    this->c = - a * A.getX() - b * A.getY();
}

int NormalFormLine::compare(Point &A) {
    int res = a * A.getX() + b * A.getY() + c;
    if (res > 0) {
        return 1;
    } else if (res == 0) {
        return 0;
    }
    return -1;
}

// v(p, A) = abs(a * a1 + b * a2 + c) / sqrt(a * a + b * b)
double NormalFormLine::getDistance(Point &A) {
    double t = a * A.getX() + b * A.getY() + c;

    if (t < 0) t *= -1; // abs()

    return t * invsqrt;
}

void NormalFormLine::Print() const {
    cout << " nfl : " << a << " * x + " << b << " * y + " << c << " = 0" << endl;
}
