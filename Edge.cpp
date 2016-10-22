//
// Created by fsoukup on 22.10.2016.
//

#include "Edge.h"

Edge::Edge(Point *a, Point *b) : a(a), b(b) {}

void Edge::Print() {
    cout << "Edge" << endl;
    cout << "A : ";
    a->Print();
    cout << "B : ";
    b->Print();
}
