//
// Created by fsoukup on 16.10.2016.
//

#include "Point.h"

Point::Point(int x, int y) : x(x), y(y) {}

Point::~Point() {}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}
