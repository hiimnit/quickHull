//
// Created by fsoukup on 16.10.2016.
//

#include "quickHull.h"

quickHull::quickHull(vector<Point *> &points) {
    /*
     *  find lowest/highest x, y // maybe start with 2
     *  -> 4x NormalFormLine -> cull points
     */

    result = new vector<Point *>();

    // taky nicmoc
    // proc je tohle vsechno v konstruktoru ?

    Point * leftmost = points.at(0), * rightmost = points.at(0);

    // wonky - tezko rict jestli funguje poradne
    for(auto p : points) {
        if (p->getX() < leftmost->getX()) {
            leftmost = p;
        } else if (p->getX() > rightmost->getX()) {
            rightmost = p;
        }
    }

    NormalFormLine * nfl = new NormalFormLine(*leftmost, *rightmost);

    vector<Point *> * up = new vector<Point *>();
    vector<Point *> * down = new vector<Point *>();

    for(auto p : points) {
        int i = nfl->compare(*p);
        if(i > 0) up->push_back(p);
        if(i < 0) down->push_back(p);

        // uz tady jde najit nejvzdalenejsi bod ? -> netreba posilat nfl
    }

    // nejspi treba poslat i nfl ?
    findHull(*leftmost, *rightmost, *up, *nfl);
    // findHull(*rightmost, *leftmost, *down, *nfl);

    // smazat up, down ?
    delete up;
    delete down;
    delete nfl;
}

// nejspi treba poslat i nfl ?
// spravne porovnavat double
// spravne porovnavat double
// spravne porovnavat double
void quickHull::findHull(Point &left, Point &right, vector<Point *> &points, NormalFormLine &nfl) {
    double f = 0, temp;
    Point * furthest = NULL;
    for(auto p : points) {
        temp = nfl.getDistance(*p);
        if(temp > f) {
            f = temp;
            furthest = p;
        }
    }

    if (furthest == NULL) {
        // push result
        // push result
        // push result

        cout << "Adding : " << endl;
        left.Print();
        right.Print();

        return;
    }

    NormalFormLine * nfl1 = new NormalFormLine(left, *furthest);
    NormalFormLine * nfl2 = new NormalFormLine(*furthest, right);

    vector<Point *> * leftPoints = new vector<Point *>();
    vector<Point *> * rightPoints = new vector<Point *>();


    for(auto p : points) {
        int i = nfl1->compare(*p);
        if(i > 0) leftPoints->push_back(p);
        int y = nfl2->compare(*p);
        if(y > 0) rightPoints->push_back(p);

        if(i > 0 && y > 0) cout << "conflict" << endl;
    }

    findHull(left, *furthest, *leftPoints, *nfl1);
    findHull(*furthest, right, *rightPoints, *nfl2);
}

quickHull::~quickHull() {
    delete result;
}
