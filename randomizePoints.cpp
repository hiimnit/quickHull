//
// Created by fsoukup on 16.10.2016.
//

#include "randomizePoints.h"

vector<Point *> * randomizePoints::getPoints(int n) {
    //set<Point *, PointPointerCmp> *resultSet = new set<Point *, PointPointerCmp>();
    vector<Point *> *res = new vector<Point *>();

    if (!n) { /*
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
        */
        Point * p0 = new Point(); p0->x = 0; p0->y = 0; res->push_back(p0);
        Point * p1 = new Point(); p1->x =-3; p1->y = 0; res->push_back(p1);
        Point * p2 = new Point(); p2->x = 4; p2->y = 0; res->push_back(p2);
        Point * p3 = new Point(); p3->x = 0; p3->y = 2; res->push_back(p3);
        Point * p4 = new Point(); p4->x = 1; p4->y = 1; res->push_back(p4);
        Point * p5 = new Point(); p5->x = 2; p5->y = 1; res->push_back(p5);
        Point * p6 = new Point(); p6->x =-2; p6->y = 1; res->push_back(p6);
        Point * p7 = new Point(); p7->x = 0; p7->y =-2; res->push_back(p7);
        Point * p8 = new Point(); p8->x =-1; p8->y =-1; res->push_back(p8);
        Point * p9 = new Point(); p9->x = 1; p9->y =-1; res->push_back(p9);
        Point * pa = new Point(); pa->x = 2; pa->y =-1; res->push_back(pa);

    } else { /*
        srand (time(NULL));
        int x = 50000;
        cout << "grid : <-" << x/2 << ", " << x/2 << ">" << endl;
        while (resultSet->size() != (unsigned int)n) {
            Point * p = new Point(rand() % x - x/2, rand() % x - x/2);
            pair<set<Point *>::iterator, bool> resPair;
            resPair = resultSet->insert(p);
            if(!resPair.second) delete p;
        }
        */

        srand(time(NULL));
        int x = 0, z;
        while (x < n) {
            int y = 0;
            x += rand() % 500;
            while ((y = rand() % 10) && y < n) {
                y += rand() % 500;
                Point * p = new Point();
                p->x = x;
                p->y = y;
                res->push_back(p);
            }
        }
    }

    cout << "# points generated : " << res->size() << endl;

    /*
    res->assign(resultSet->begin(), resultSet->end());
    delete resultSet;
     */
    cout << "points generated" << endl;
    return res;
}

