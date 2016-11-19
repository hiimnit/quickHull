#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "quickHull.h"
#include "readPoints.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point {
public:
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    double x;
    double y;
    friend ostream& operator<<(ostream& stream, const Point& point) {
        stream << setprecision(16) << point.x << " " << point.y;
        return stream;
    }
};

class NormalFormLine {
    // p : a * x + b * y + c = 0
    // A[a1, a2]
    // v(p, A) = abs(a * a1 + b * a2 + c) / sqrt(a * a + b * b)
    // 1 / sqrt(a * a + b * b) - used a ton
    //  => invsqrt = 1 / sqrt(a * a + b * b)
    double a, b, c;
    double invsqrt; // invsqrt = 1 / sqrt(a * a + b * b)
public:
    NormalFormLine(Point * A, Point * B) {
        // normal vector = vector + swap
        a = (B->y - A->y) * -1;
        b = B->x - A->x;
        c = -a * A->x - b * A->y;
        invsqrt = 1 / sqrt(a * a + b * b); // useless ?
    }
    int compare(Point * P) {
        double res = a * P->x + b * P->y + c;

        if (res > 0) return 1;
        return -1;
    }
    double getDistance(Point * P) {
        double t = a * P->x + b * P->y + c;
        t = abs(t);
        return t * invsqrt;             // netreba
    }
};

vector<Point *> * getPoints(string file) {
    vector<Point *> * res = new vector<Point *>();

    fstream fs(file, fstream::in);
    char line[256];
    int number;
    double x, y;

    if(!fs.is_open()) {
        cout << "Failed to open " << file << endl;
        return NULL;
    }

    fs.getline(line, 256);
    fs >> number;
    cout << "Reading " << number << " points" << endl;
    while(number-- > 0) {
        fs >> x;
        fs >> y;
        res->push_back(new Point(x, y));
    }

    fs.close();
    return res;
}

bool cmp(const Point * left, const Point * right) {
    if (left->x == right->x) return left->y < right->y;
    return left->x < right->x;
}

bool checkPoints(string file, vector<Point *> * myResult) {
    int number;
    double x, y;
    fstream fs(file, fstream::in);
    if(!fs.is_open()) {
        cout << "Failed to open " << file << endl;
        return false;
    }

    fs >> number; // reading dimension number
    fs >> number; // reading points number

    if(number != myResult->size()) {
        fs.close();
        return false;
    }

    vector<Point *> * res = new vector<Point *>();
    while(number-- > 0) {
        fs >> x;
        fs >> y;
        res->push_back(new Point(x, y));
    }


    if(res->size() != myResult->size()) {
        fs.close();
        for(int i = 0; i < res->size(); ++i) delete res->at(i);
        delete res;
        return false;
    }


    sort(myResult->begin(), myResult->end(), cmp);
    sort(res->begin(), res->end(), cmp);



    for(int i = 0; i < myResult->size(); ++i) {
        if (myResult->at(i)->x != res->at(i)->x || myResult->at(i)->y != res->at(i)->y) {
            fs.close();
            for(int i = 0; i < res->size(); ++i) delete res->at(i);
            delete res;
            return false;
        }
    }

    fs.close();
    for(int i = 0; i < res->size(); ++i) delete res->at(i);
    delete res;
    return true;
}

quickHull::quickHull(vector<Point *> *p) : points(p) {
    result = new vector<Point *>();
}

void quickHull::findHull(Point *left, Point *right, int * pointsPointer, int end, NormalFormLine *nfl, int dir) {
    if (left->x == right->x && left->y == right->y) return;
    double f = 0, temp;
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
        if (temp >= 0) {
            pointsPointer[s1++] = pointsPointer[i];
        }
    }
    s2 = s1;
    for(int i = j + 1; i < end; ++i) { // preskocim furthest ?
        temp = nfl2->compare(points->at(pointsPointer[i]));
        if (temp >= 0) {
            pointsPointer[s2++] = pointsPointer[i];
        }
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
}

vector<Point *> * quickHull::run() {
    if (points->size() <= 3) {
        if (points->size() == 3) {
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
    Point *leftmost = points->at(0);
    Point *rightmost = points->at(points->size() - 1);
    Point *topmost = points->at(0);
    int T;
    Point *bottommost = points->at(0);
    int B;

    int q = 0;
    for (auto p : *points) {
        if (p->y < bottommost->y) {
            bottommost = p;
            B = q;
        } else if (p->y > topmost->y) {
            topmost = p;
            T = q;
        }
        q++;
    }

    int *pointsPointer1 = new int[points->size()];
    int *pointsPointer2 = new int[points->size()];

    NormalFormLine *nfl1 = new NormalFormLine(leftmost, topmost);
    NormalFormLine *nfl2 = new NormalFormLine(topmost, rightmost);
    NormalFormLine *nfl3 = new NormalFormLine(rightmost, bottommost);
    NormalFormLine *nfl4 = new NormalFormLine(bottommost, leftmost);

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
        if (i >= 0) {
            pointsPointer1[s1++] = p;
            continue;
        }
        i = nfl4->compare(points->at(p));
        if (i >= 0) {
            pointsPointer2[s4++] = p;
        }
    }
    // zbytek nfl1 nebo 4 a zacatek nfl2 nebo 3
    if (min == T) { // pokud min == T pak je nfl1 hotova
        s2 = s1;
        for (int p = min + 1; p < max; ++p) { // min preskocim ?
            i = nfl2->compare(points->at(p));
            if (i >= 0) {
                pointsPointer1[s2++] = p;
                continue;
            }
            i = nfl4->compare(points->at(p));
            if (i >= 0) {
                pointsPointer2[s4++] = p;
            }
        }
        s3 = s4;
    } else {
        s3 = s4;
        for (int p = min + 1; p < max; ++p) { // min preskocim ?
            i = nfl1->compare(points->at(p));
            if (i >= 0) {
                pointsPointer1[s1++] = p;
                continue;
            }
            i = nfl3->compare(points->at(p));
            if (i >= 0) {
                pointsPointer2[s3++] = p;
            }
        }
        s2 = s1;
    }

    for (int p = max + 1; p < points->size(); ++p) { // max preskocim ?
        i = nfl2->compare(points->at(p));
        if (i >= 0) {
            pointsPointer1[s2++] = p;
            continue;
        }
        i = nfl3->compare(points->at(p));
        if (i >= 0) {
            pointsPointer2[s3++] = p;
        }
    }

    // nfl nebudu posilat ?
    findHull(leftmost, topmost, pointsPointer1, s1, nfl1, 0);
    findHull(topmost, rightmost, pointsPointer1 + s1, s2 - s1, nfl2, 0);
    findHull(rightmost, bottommost, pointsPointer2 + s4, s3 - s4, nfl3, 1);
    findHull(bottommost, leftmost, pointsPointer2, s4, nfl4, 1);

    delete[] pointsPointer1;
    delete[] pointsPointer2;

    delete nfl1;
    delete nfl2;
    delete nfl3;
    delete nfl4;

    return result;
}


int main(int argc, char* argv[]) {
    string file, test;
    if(argc != 3) {
        cout << "usage : ./out.o infile resfile" << endl;
    }

    file = argv[1];
    test = argv[2];

    // read points
    vector<Point *> * points = getPoints(file);
    if (points == NULL) {
        return -1;
    }

    // algorithm
    cout << "time : ";
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    quickHull * qH = new quickHull(points);
    vector<Point *> * results = qH->run();
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << time_span.count() << endl;

    cout << results->size() << " point in convex hull" << endl;

    // test
    if (test != "0") {
        if (checkPoints(test, results)) cout << "correct" << endl;
        else cout << "incorrect" << endl;
    }

    // cleanup
    for(size_t i = 0; i < points->size(); ++i) delete points->at(i);
    delete qH;
    delete points;
    return 0;
}