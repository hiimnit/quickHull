//
// Created by fsoukup on 16.10.2016.
//

#include "randomizePoints.h"

vector<Point *> * randomizePoints::getPoints(int n) {
    set<Point *, PointPointerCmp> *resultSet = new set<Point *, PointPointerCmp>();
    vector<Point *> *res = new vector<Point *>();

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
    } else if (n == 1) {
        resultSet->insert(new Point(-4, 0));
        resultSet->insert(new Point(-3, 3));
        resultSet->insert(new Point(-2, 2));
        resultSet->insert(new Point(-1, 1));
        resultSet->insert(new Point(0, 4));

    } else {
        srand (time(NULL));
        while (resultSet->size() != (unsigned int)(10 * n)) {
            resultSet->insert(new Point(rand() % n - n/2, rand() % n - n/2));
        }
    }

    res->assign(resultSet->begin(), resultSet->end());
    return res;
}

