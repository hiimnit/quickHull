//
// Created by fsoukup on 16.10.2016.
//

#include "randomizePoints.h"

vector<Point *> * randomizePoints::getPoints(int n) {
    vector<Point *> * resultSet = new vector<Point *>();


    if (!n) {
        resultSet->push_back(new Point(0, 0));
        resultSet->push_back(new Point(-3, 0));
        resultSet->push_back(new Point(4, 0));
        resultSet->push_back(new Point(0, 2));
        resultSet->push_back(new Point(1, 1));
        resultSet->push_back(new Point(2, 1));
        resultSet->push_back(new Point(-2, 1));
        resultSet->push_back(new Point(0, -2));
        resultSet->push_back(new Point(-1, -1));
        resultSet->push_back(new Point(1, -1));
        resultSet->push_back(new Point(2, -1));
    } else {
        srand (time(NULL));
        while (resultSet->size() != n) {
            resultSet->push_back(new Point(rand() % 10000 - 5000, rand() % 10000 - 5000));
        }
    }

    return resultSet;
}

