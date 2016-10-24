//
// Created by fsoukup on 16.10.2016.
//

#include "NormalFormLine.h"

NormalFormLine::NormalFormLine(Point &A, Point &B, int dir) : A(A), B (B) {
    // normal vector = vector + swap
    a = (B.getY() - A.getY()) * -1;
    b = B.getX() - A.getX();
    c = -a * A.getX() - b * A.getY();
    invsqrt = 1 / sqrt(a * a + b * b);

    if (dir == 0) {
        X = new Point(A.getX(), B.getY());
    } else {
        X = new Point(B.getX(), A.getY());
    }
}
int NormalFormLine::compare(Point &P) {
    int res = a * P.getX() + b * P.getY() + c;
    if (!res) {
        return -1;
    }

    double a1 = area(P, B, *X);
    double a2 = area(P, A, *X);
    double a3 = area(P, A, B);

    double a  = area(A, B, *X);

    if (abs(a - a1 - a2 - a3) < 0.00001) return 1;

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
    cout << " x   : "; X->Print();
    cout << " a   : "; A.Print();
    cout << " b   : "; B.Print();
}
