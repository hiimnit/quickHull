//
// Created by fsoukup on 16.10.2016.
//

#include "NormalFormLine.h"

NormalFormLine::NormalFormLine(Point *A, Point *B) {
    // normal vector = vector + swap
    a = (B->y - A->y) * -1;
    b = B->x - A->x;
    c = -a * A->x - b * A->y;

    invsqrt = 1 / sqrt(a * a + b * b); // useless ?
}
int NormalFormLine::compare(Point *P) {
    double res = a * P->x + b * P->y + c;

    if (abs(res) < 0.000000000001) {
        return -1; // point on line
    }

    if (res > 0) {
        return 1;
    }

    return -1;
}

// v(p, A) = abs(a * a1 + b * a2 + c) / sqrt(a * a + b * b)
double NormalFormLine::getDistance(Point * A) {
    double t = a * A->x + b * A->y + c;

    if (t < 0) t *= -1; // abs()

    return t * invsqrt; // je treba prenasobit vse stejnou kladnou hodnotou ?
}

void NormalFormLine::Print() const {
    cout << " nfl : " << setprecision(16) << a << " * x + " << b << " * y + " << c << " = 0" << endl;
}
