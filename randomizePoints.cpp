//
// Created by fsoukup on 16.10.2016.
//

#include "randomizePoints.h"

vector<Point *> * randomizePoints::getPoints(int n) {
    set<Point *, PointPointerCmp> * resultSet = new set<Point *, PointPointerCmp>();
    vector<Point *> * res = new vector<Point *>();

    if (!n) {
        resultSet->insert(new Point(0, 0));
        resultSet->insert(new Point(-3, 0));
        resultSet->insert(new Point(4, 0));
        resultSet->insert(new Point(0, 2));
        resultSet->insert(new Point(1, 1));
        resultSet->insert(new Point(2, 1));
        resultSet->insert(new Point(-2, 1));
        resultSet->insert(new Point(0, -2));
        resultSet->insert(new Point(-1, -1));
        resultSet->insert(new Point(1, -1));
        resultSet->insert(new Point(2, -1));
    } else {
        srand (time(NULL));
        while (resultSet->size() != n) {
            resultSet->insert(new Point(rand() % 10000 - 5000, rand() % 10000 - 5000));
        }
    }

    res->assign(resultSet->begin(), resultSet->end());
    return res;
}

