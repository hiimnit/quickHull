//
// Created by fsoukup on 16.10.2016.
//

#include "quickHull.h"

bool c(Point* left, Point* right) {
    if (left->x == right->x) return left->y < right->y;
    return left->x < right->x;
}

quickHull::quickHull(vector<Point *> *p) : points(p) {
    result = new vector<Point *>();
    // pointsPointer = new int(points.size());
}

void quickHull::findHull(Point *left, Point *right, int * pointsPointer, int end, NormalFormLine *nfl, int dir) {
    if (left->x == right->x && left->y == right->y) return;
    float f = 0, temp;
    int j;
    Point * furthest = NULL;
    for(int i = 0; i < end; ++i) {
        temp = nfl->getDistance(points->at(pointsPointer[i]));
        if(temp > f) {
            f = temp;
            furthest = points->at(pointsPointer[i]);
            j = i;
        }
    }

    // pridat kdyz lezi na primce ?

    if (furthest == NULL) {
        result->push_back(right);
        return;
    }

    NormalFormLine *nfl1, *nfl2;
    if (dir) {
        nfl2 = new NormalFormLine(left, furthest);
        nfl1 = new NormalFormLine(furthest, right);
    } else {
        nfl1 = new NormalFormLine(left, furthest);
        nfl2 = new NormalFormLine(furthest, right);

    }

    /*
    vector<Point *> * leftPoints = new vector<Point *>();
    vector<Point *> * rightPoints = new vector<Point *>();

    //int j, s1 = start, s2 = start;
    for(int i = start; i < end; ++i) {
        j = nfl1->compare(*(points.at(pointsPointer[i])));
        if(j > 0) {
            pointsPointer[s1++] = pointsPointer[i];
            s2++;
            continue;
        }
        j = nfl2->compare(*(points.at(pointsPointer[i])));
        if(j > 0) {
            pointsPointer[s2++] = pointsPointer[i];
        }
    }
    */
    int s1 = 0, s2 = 0;
    for(int i = 0; i < j; ++i) {
        temp = nfl1->compare(points->at(pointsPointer[i]));
        if (temp > 0) {
            pointsPointer[s1++] = pointsPointer[i];
        }
    }
    s2 = s1;
    for(int i = j + 1; i < end; ++i) { // preskocim furthest ?
        temp = nfl2->compare(points->at(pointsPointer[i]));
        if (temp > 0) {
            pointsPointer[s2++] = pointsPointer[i];
        }
    }

    if (dir) {
        cout << "furthest : " << *furthest << endl;
        cout << "ss1 : " << endl;
        for (int i = 0; i < s1; ++i) cout << *(points->at(pointsPointer[i])) << endl;
        cout << "ss2 : " << endl;
        for (int i = 0; i < s2 - s1; ++i) cout << *(points->at((pointsPointer + s1)[i])) << endl;
    }

    if(dir) {
        findHull(left, furthest, pointsPointer + s1, s2 - s1, nfl2, dir);
        findHull(furthest, right, pointsPointer, s1, nfl1, dir);
    } else {
        findHull(left, furthest, pointsPointer, s1, nfl1, dir);
        findHull(furthest, right, pointsPointer + s1, s2 - s1, nfl2, dir);
    }

    delete nfl1;
    delete nfl2;
    /*
    delete leftPoints;
    delete rightPoints;
    */
}

quickHull::~quickHull() {
    delete result;
    // delete[] pointsPointer;
}

vector<Point *> * quickHull::run() {
    if (points->size() <= 3) {
        if(points->size() == 3) {
            result->push_back(points->at(0));
            result->push_back(points->at(1));
            result->push_back(points->at(2));
        }
        return result;
    }

    // sort
    sort(points->begin(), points->end(), c);

    int s1 = 0, s2 = 0, s3 = 0, s4 = 0; // pomocne hodnoty

    // leftmost je ted prvni, rightmost posledni
    Point * leftmost = points->at(0);
    Point * rightmost = points->at(points->size() - 1);
    Point * topmost = points->at(0); int T;
    Point * bottommost = points->at(0); int B;

    int q = 0;
    for(auto p : *points) {
        /*
        if (p->x < leftmost->x) {
            leftmost = p;
        } else if (p->x > rightmost->x) {
            rightmost = p;
        }
        */
        if (p->y < bottommost->y) {
            bottommost = p;
            B = q;
        } else if (p->y > topmost->y) {
            topmost = p;
            T = q;
        }
        q++;
    }

    int * pointsPointer1 = new int[points->size()];
    int * pointsPointer2 = new int[points->size()];

    NormalFormLine * nfl1 = new NormalFormLine(leftmost, topmost);
    NormalFormLine * nfl2 = new NormalFormLine(topmost, rightmost);
    NormalFormLine * nfl3 = new NormalFormLine(rightmost, bottommost);
    NormalFormLine * nfl4 = new NormalFormLine(bottommost, leftmost);

    cout << "leftmost    : " << *leftmost   << endl;
    cout << "topmost     : " << *topmost    << endl;
    cout << "rightmost   : " << *rightmost  << endl;
    cout << "bottommost  : " << *bottommost << endl;

    /*
    vector<Point *> * lt = new vector<Point *>();
    vector<Point *> * tr = new vector<Point *>();
    vector<Point *> * rb = new vector<Point *>();
    vector<Point *> * bl = new vector<Point *>();
    */

    // pokud budou serazene, muzu rozdelit na casti porovnavani
    int i, k = 0;
    /*
    for(auto p : points) {
        i = nfl1->compare(*p);
        if (i > 0) {
            pointsPointer[s1++] = k;
            s2++; s3++; s4++;
            continue;
        }
        i = nfl2->compare(*p);
        if (i > 0) {
            pointsPointer[s2++] = k;
            s3++; s4++;
            continue;
        }
        i = nfl3->compare(*p);
        if (i > 0) {
            pointsPointer[s3++] = k;
            s4++;
            continue;
        }
        i = nfl4->compare(*p);
        if (i > 0) {
            pointsPointer[s4++] = k;
        }
        k++;
    }
    */
    int min = T < B ? T : B;
    int max = T < B ? B : T;
    // prvni cast / nfl1 a nfl4
    for (int p = 1; p < min; ++p) { // p i min preskocim, nemusim pak resit ve findhull?
        i = nfl1->compare(points->at(p));
        if (i > 0) {
            pointsPointer1[s1++] = p;
            continue;
        }
        i = nfl4->compare(points->at(p));
        if (i > 0) {
            pointsPointer2[s4++] = p;
        }
    }
    // zbytek nfl1 nebo 4 a zacatek nfl2 nebo 3
    if (min == T) { // pokud min == T pak je nfl1 hotova
        s2 = s1;
        for (int p = min + 1; p < max; ++p) { // min preskocim ?
            i = nfl2->compare(points->at(p));
            if (i > 0) {
                pointsPointer1[s2++] = p;
                continue;
            }
            i = nfl4->compare(points->at(p));
            if (i > 0) {
                pointsPointer2[s4++] = p;
            }
        }
        s3 = s4;
    } else {
        s3 = s4;
        for (int p = min + 1; p < max; ++p) { // min preskocim ?
            i = nfl1->compare(points->at(p));
            if (i > 0) {
                pointsPointer1[s1++] = p;
                continue;
            }
            i = nfl3->compare(points->at(p));
            if (i > 0) {
                pointsPointer2[s3++] = p;
            }
        }
        s2 = s1;
    }

    nfl2->Print();
    nfl1->Print();
    nfl3->Print();
    nfl4->Print();
    for (int p = max + 1; p < points->size(); ++p) { // max preskocim ?
        i = nfl2->compare(points->at(p));
        if (i > 0) {
            pointsPointer1[s2++] = p;
            continue;
        }
        i = nfl3->compare(points->at(p));
        if (i > 0) {
            pointsPointer2[s3++] = p;
        }
    }

    cout << "s1" << endl;
    for(int i = 0; i < s1; ++i) cout << *(points->at(pointsPointer1[i])) << endl;
    cout << "s2" << endl;
    for(int i = 0; i < s2 - s1; ++i) cout << *(points->at((pointsPointer1 + s1)[i])) << endl;
    cout << "s3" << endl;
    for(int i = 0; i < s3 - s4; ++i) cout << *(points->at((pointsPointer2 + s4)[i])) << endl;
    cout << "s4" << endl;
    for(int i = 0; i < s4; ++i) cout << *(points->at(pointsPointer2[i])) << endl;

    // nfl nebudu posilat ?
    findHull(leftmost, topmost, pointsPointer1, s1, nfl1, 0);
    findHull(topmost, rightmost, pointsPointer1 + s1, s2 - s1, nfl2, 0);
    findHull(rightmost, bottommost, pointsPointer2 + s4, s3 - s4, nfl3, 1);
    cout << "trouble" << endl<< endl<< endl<< endl<< endl<< endl<< endl<< endl;
    findHull(bottommost, leftmost, pointsPointer2, s4, nfl4, 1);

    /*
    delete lt;
    delete tr;
    delete rb;
    delete bl;
    */
    //delete[] pointsPointer1;
    //delete[] pointsPointer2;

    delete nfl1;
    delete nfl2;
    delete nfl3;
    delete nfl4;

    return result;
}

