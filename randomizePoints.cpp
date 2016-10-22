//
// Created by fsoukup on 16.10.2016.
//

#include "randomizePoints.h"

vector<Point *> * randomizePoints::getPoints(int n) {
    vector<Point *> * resultSet = new vector<Point *>();

    resultSet->push_back(new Point(0, 0));
    resultSet->push_back(new Point(-3, 0));
    resultSet->push_back(new Point(4, 0));
    resultSet->push_back(new Point(0, 2));
    resultSet->push_back(new Point(1, 1));
    resultSet->push_back(new Point(2, 1));
    resultSet->push_back(new Point(-2, 1));


    return resultSet;
}
