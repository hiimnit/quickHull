//
// Created by fsoukup on 16.10.2016.
//

#include "quickHull.h"

// nejspi treba poslat i nfl ?
void quickHull::findHull(Point &left, Point &right, vector<Point *> &points) {
    return;
}

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
    findHull(*leftmost, *rightmost, *up);
    findHull(*rightmost, *leftmost, *down);

    // smazat up, down ?
    delete up;
    delete down;
    delete nfl;
}

quickHull::~quickHull() {
    delete result;
}
