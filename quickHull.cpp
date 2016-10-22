//
// Created by fsoukup on 16.10.2016.
//

#include "quickHull.h"

quickHull::quickHull(vector<Point *> &p) : points(p) {
    result = new vector<Edge *>();
}

// nejspi treba poslat i nfl ?
void quickHull::findHull(Point &left, Point &right, vector<Point *> &points, NormalFormLine &nfl) {

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
        result->push_back(new Edge(&left, &right));
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

    findHull(left, *furthest, *leftPoints, *nfl1);
    findHull(*furthest, right, *rightPoints, *nfl2);

    delete nfl1;
    delete nfl2;
    delete leftPoints;
    delete rightPoints;
}

quickHull::~quickHull() {
    delete result;
}

vector<Edge *> &quickHull::execute() {
    /*
     *  find lowest/highest x, y // maybe start with 2
     *  -> 4x NormalFormLine -> cull points
     */

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

    for(auto p : points) {
        int i = nfl->compare(*p);
        if(i >= 0) up->push_back(p);
        if(i <= 0) down->push_back(p);
    }

    findHull(*leftmost, *rightmost, *up, *nfl);
    findHull(*rightmost, *leftmost, *down, *nfl);

    // vratit rightmost a lefmost - pro odstaneni
    points.push_back(rightmost);
    points.push_back(leftmost);

    delete up;
    delete down;
    delete nfl;

    return *result;
}

