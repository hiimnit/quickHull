//
// Created by fsoukup on 16.10.2016.
//

#include "quickHull.h"

quickHull::quickHull(vector<Point *> &p) : points(p) {
    result = new vector<Edge *>();
}

// nejspi treba poslat i nfl ?
void quickHull::findHull(Point &left, Point &right, vector<Point *> &points, NormalFormLine &nfl, int dir) {
    if (left == right) return;

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
        result->push_back(new Edge(&left, &right));
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

    delete nfl1, nfl2;
    delete leftPoints, rightPoints;
}

quickHull::~quickHull() {
    for(int i = 0; i < result->size(); ++i) delete result->at(i);
    delete result;
}

vector<Edge *> &quickHull::run() {
    if (points.size() <= 3) {
        if(points.size() == 3) {
            result->push_back(new Edge(points.at(0), points.at(1)));
            result->push_back(new Edge(points.at(1), points.at(2)));
            result->push_back(new Edge(points.at(2), points.at(0)));
        }
        return *result;
    }

    Point * leftmost = points.at(0), * rightmost = points.at(0), * topmost = points.at(0), * bottommost = points.at(0);

    for(auto p : points) {
        if (p->getX() < leftmost->getX()) {
            leftmost = p;
        }
        if (p->getX() > rightmost->getX()) {
            rightmost = p;
        }
        if (p->getY() < bottommost->getY()) {
            bottommost = p;
        }
        if (p->getY() > topmost->getY()) {
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

    int i, j, k, l;
    for(auto p : points) {
        i = nfl1->compare(*p);
        if (i > 0) {
            lt->push_back(p);
            continue;
        }
        j = nfl2->compare(*p);
        if (j > 0) {
            tr->push_back(p);
            continue;
        }
        k = nfl3->compare(*p);
        if (k > 0) {
            rb->push_back(p);
            continue;
        }
        l = nfl4->compare(*p);
        if (l > 0) {
            bl->push_back(p);
        }
    }

    findHull(*leftmost, *topmost, *lt, *nfl1, 0);
    findHull(*topmost, *rightmost, *tr, *nfl2, 1);
    findHull(*rightmost, *bottommost, *rb, *nfl3, 0);
    findHull(*bottommost, *leftmost, *bl, *nfl4, 1);

    delete lt, tr, rb, bl;
    delete nfl1, nfl2, nfl3, nfl4;

    return *result;
}

