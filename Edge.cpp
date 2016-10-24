//
// Created by fsoukup on 22.10.2016.
//

#include "Edge.h"

Edge::Edge(Point & A, Point &B) : A(A), B(B) {}

void Edge::Print() {
    cout << "Edge" << endl;
    cout << "A : ";
    A.Print();
    cout << "B : ";
    B.Print();
}
