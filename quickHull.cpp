//
// Created by fsoukup on 16.10.2016.
//

#include "quickHull.h"

quickHull::quickHull(vector<Point *> &p) : points(p) {
    result = new vector<Point *>();
}

void quickHull::findHull(Point &left, Point &right, vector<Point *> &points, NormalFormLine &nfl, int dir) {
    if (left.x == right.x && left.y == right.y) return;

    float f = 0, temp;
    Point * furthest = NULL;
    for(auto p : points) {
        temp = nfl.getDistance(*p);
        if(temp > f) {
            f = temp;
            furthest = p;
        }
    }

    // pridat kdyz lezi na primce ?

    if (furthest == NULL) {
        // correct ?
        result->push_back(&right);
        return;
    }

    NormalFormLine * nfl1 = new NormalFormLine(left, *furthest, dir);
    NormalFormLine * nfl2 = new NormalFormLine(*furthest, right, dir);

    vector<Point *> * leftPoints = new vector<Point *>();
    vector<Point *> * rightPoints = new vector<Point *>();

    int i, y;
    for(auto p : points) {
        i = nfl1->compare(*p);
        if(i > 0) {
            leftPoints->push_back(p);
            continue;
        }
        y = nfl2->compare(*p);
        if(y > 0) rightPoints->push_back(p);
    }

    findHull(left, *furthest, *leftPoints, *nfl1, dir);
    findHull(*furthest, right, *rightPoints, *nfl2, dir);

    delete nfl1;
    delete nfl2;
    delete leftPoints;
    delete rightPoints;
}

quickHull::~quickHull() {
    delete result;
}

vector<Point *> &quickHull::run() {
    if (points.size() <= 3) {
        if(points.size() == 3) {
            result->push_back(points.at(0));
            result->push_back(points.at(1));
            result->push_back(points.at(2));
        }
        return *result;
    }

    Point * leftmost = points.at(0), * rightmost = points.at(0), * topmost = points.at(0), * bottommost = points.at(0);

    for(auto p : points) {
        if (p->x < leftmost->x) {
            leftmost = p;
        } else if (p->x > rightmost->x) {
            rightmost = p;
        }
        if (p->y < bottommost->y) {
            bottommost = p;
        } else if (p->y > topmost->y) {
            topmost = p;
        }
    }

    NormalFormLine * nfl1 = new NormalFormLine(*leftmost, *topmost, 0);
    NormalFormLine * nfl2 = new NormalFormLine(*topmost, *rightmost, 1);
    NormalFormLine * nfl3 = new NormalFormLine(*rightmost, *bottommost, 0);
    NormalFormLine * nfl4 = new NormalFormLine(*bottommost, *leftmost, 1);

    vector<Point *> * lt = new vector<Point *>();
    vector<Point *> * tr = new vector<Point *>();
    vector<Point *> * rb = new vector<Point *>();
    vector<Point *> * bl = new vector<Point *>();

    // pokud budou serazene, muzu rozdelit na casti porovnavani
    int i;
    for(auto p : points) {
        i = nfl1->compare(*p);
        if (i > 0) {
            lt->push_back(p);
            continue;
        }
        i = nfl2->compare(*p);
        if (i > 0) {
            tr->push_back(p);
            continue;
        }
        i = nfl3->compare(*p);
        if (i > 0) {
            rb->push_back(p);
            continue;
        }
        i = nfl4->compare(*p);
        if (i > 0) {
            bl->push_back(p);
        }
    }

    findHull(*leftmost, *topmost, *lt, *nfl1, 0);
    findHull(*topmost, *rightmost, *tr, *nfl2, 1);
    findHull(*rightmost, *bottommost, *rb, *nfl3, 0);
    findHull(*bottommost, *leftmost, *bl, *nfl4, 1);

    delete lt;
    delete tr;
    delete rb;
    delete bl;
    delete nfl1;
    delete nfl2;
    delete nfl3;
    delete nfl4;

    return *result;
}

