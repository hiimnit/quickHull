//
// Created by fsoukup on 16.10.2016.
//

#include "NormalFormLine.h"

NormalFormLine::NormalFormLine(Point &A, Point &B, int dir) : A(A), B (B) {
    // normal vector = vector + swap
    a = (B.y - A.y) * -1;
    b = B.x - A.x;
    c = -a * A.x - b * A.y;
    invsqrt = 1 / sqrt(a * a + b * b);

    if (dir == 0) {
        X->x = A.x;
        X->y = B.y;
    } else {
        X->x = B.x;
        X->y = A.y;
    }
}
int NormalFormLine::compare(Point &P) {
    int res = a * P.x + b * P.y + c;
    // if res == 0 then point on line
    if (!res) {
        return -1;
    }

    // comparing using areas
    double a1 = area(P, B, *X);
    double a2 = area(P, A, *X);
    double a3 = area(P, A, B);

    double a  = area(A, B, *X); // tohle se takz pocita casto

    if (abs(a - a1 - a2 - a3) < 0.00001) return 1;

    return -1;
}

// v(p, A) = abs(a * a1 + b * a2 + c) / sqrt(a * a + b * b)
double NormalFormLine::getDistance(Point &A) {
    double t = a * A.x + b * A.y + c;

    if (t < 0) t *= -1; // abs()

    return t * invsqrt;
}

void NormalFormLine::Print() const {
    cout << " nfl : " << a << " * x + " << b << " * y + " << c << " = 0" << endl;
    cout << " x   : " << "X_x : " << X->x << " | X_y : " << X->y << endl;
    cout << " a   : " << "A_x : " << A.x << " | A_y : " << A.y << endl;
    cout << " b   : " << "B_x : " << B.x << " | B_y : " << B.y << endl;
}
