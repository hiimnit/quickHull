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
    } else {
        srand (time(NULL));
        int x = 50000;
        cout << "grid : <-" << x/2 << ", " << x/2 << ">" << endl;
        while (resultSet->size() != (unsigned int)n) {
            Point * p = new Point(rand() % x - x/2, rand() % x - x/2);
            pair<set<Point *>::iterator, bool> resPair;
            resPair = resultSet->insert(p);
            if(!resPair.second) delete p;
        }
    }

    res->assign(resultSet->begin(), resultSet->end());
    cout << "points generated" << endl;
    return res;
}

