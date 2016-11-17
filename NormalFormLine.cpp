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
    float res = a * P->x + b * P->y + c;


    cout << "  res : " << res << " | point : " << *P << endl;
    if (res > 0) {
        return 1; // todo confirm
    }

    /*
    // if res == 0 then point on line
    // pokud budu vracet -1 tak useless
    if (res == 0) {
        return -1;
    }
    */

    /*
    // comparing using areas
    double a1 = area(P, B, *X);
    double a2 = area(P, A, *X);
    double a3 = area(P, A, B);

    double a  = area(A, B, *X); // tohle se takz pocita casto

    if (abs(a - a1 - a2 - a3) < 0.00001) return 1;
    */
    return -1;
}

// v(p, A) = abs(a * a1 + b * a2 + c) / sqrt(a * a + b * b)
float NormalFormLine::getDistance(Point * A) {
    float t = a * A->x + b * A->y + c;

    if (t < 0) t *= -1; // abs()

    return t; // * invsqrt; // je treba prenasobit vse stejnou kladnou hodnotou ?
}

void NormalFormLine::Print() const {
    cout << " nfl : " << setprecision(16) << a << " * x + " << b << " * y + " << c << " = 0" << endl;
}
