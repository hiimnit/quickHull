//
// Created by fsoukup on 22.10.2016.
//

#include "Edge.h"

Edge::Edge(Point & A, Point &B) : A(A), B(B) {}

void Edge::Print() {
    cout << "Edge : ";
    cout << "A_x : " << A.x << " | A_y : " << A.y;
    cout << " B_x : " << B.x << " | B_y : " << B.y << endl;
}
