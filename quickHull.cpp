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
    int lm = 0, rm = 0, x = 0;

    // wonky - tezko rict jestli funguje poradne
    for(auto p : points) {
        if (p->getX() < leftmost->getX()) {
            leftmost = p;
            lm = x;
        } else if (p->getX() > rightmost->getX()) {
            rightmost = p;
            rm = x;
        }
        x++;
    }

    // vyhodit leftmost a rightmost z points
    points.erase(points.begin() + rm);
    points.erase(points.begin() + lm);

    NormalFormLine * nfl = new NormalFormLine(*leftmost, *rightmost);

    vector<Point *> * up = new vector<Point *>();
    vector<Point *> * down = new vector<Point *>();


    // vyhodit leftmost a rightmost z points
    for(auto p : points) {
        int i = nfl->compare(*p);
        if(i >= 0) up->push_back(p);
        if(i <= 0) down->push_back(p);

        // uz tady jde najit nejvzdalenejsi bod ? -> netreba posilat nfl
    }

    // nejspi treba poslat i nfl ?
    findUpperHull(*leftmost, *rightmost, *up, *nfl);
    findLowerHull(*rightmost, *leftmost, *down, *nfl);

    // smazat up, down ?
    delete up;
    delete down;
    delete nfl;
}

// nejspi treba poslat i nfl ?
// spravne porovnavat double
// spravne porovnavat double
// spravne porovnavat double
void quickHull::findUpperHull(Point &left, Point &right, vector<Point *> &points, NormalFormLine &nfl) {

    double f = 0, temp;
    Point * furthest = NULL;
    int x = 0, pos = 0;
    for(auto p : points) {
        temp = nfl.getDistance(*p);
        if(temp > f || abs(temp - f) < 0.0000001) {
            f = temp;
            furthest = p;
            pos = x;
        }
        x++;
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

    // delete furthest Point from points
    points.erase(points.begin() + pos);

    NormalFormLine * nfl1 = new NormalFormLine(left, *furthest);
    NormalFormLine * nfl2 = new NormalFormLine(*furthest, right);

    vector<Point *> * leftPoints = new vector<Point *>();
    vector<Point *> * rightPoints = new vector<Point *>();

    // if i = 0 -> add
    for(auto p : points) {
        int i = nfl1->compare(*p);
        if(i >= 0) leftPoints->push_back(p);
        int y = nfl2->compare(*p);
        if(y >= 0) rightPoints->push_back(p);
    }

    findUpperHull(left, *furthest, *leftPoints, *nfl1);
    findUpperHull(*furthest, right, *rightPoints, *nfl2);
}

quickHull::~quickHull() {
    delete result;
}

void quickHull::findLowerHull(Point &left, Point &right, vector<Point *> &points, NormalFormLine &nfl) {

    cout << "findLowerHull" << endl;
    left.Print();
    right.Print();
    nfl.Print();

    double f = 0, temp;
    Point * furthest = NULL;
    int x = 0, pos = 0;
    for(auto p : points) {
        temp = nfl.getDistance(*p);
        cout << "Distance : " << temp << endl;
        if(temp > f || abs(temp - f) < 0.0000001) {
            f = temp;
            furthest = p;
            pos = x;
        }
        x++;
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

    // delete furthest Point from points
    points.erase(points.begin() + pos);

    NormalFormLine * nfl1 = new NormalFormLine(left, *furthest);
    NormalFormLine * nfl2 = new NormalFormLine(*furthest, right);

    vector<Point *> * leftPoints = new vector<Point *>();
    vector<Point *> * rightPoints = new vector<Point *>();

    // if i = 0 -> add
    for(auto p : points) {
        int i = nfl1->compare(*p);
        if(i <= 0) leftPoints->push_back(p);
        int y = nfl2->compare(*p);
        if(y <= 0) rightPoints->push_back(p);

        cout << "i : " << i << " y : " << y << endl;
        if(i < 0 && y < 0) cout << "conflict" << endl;
    }

    findLowerHull(left, *furthest, *leftPoints, *nfl1);
    findLowerHull(*furthest, right, *rightPoints, *nfl2);
}
