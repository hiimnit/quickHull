#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "quickHull.h"
#include "readPoints.h"

using namespace std;

int main(int argc, char* argv[]) {
    /*
    int n;
    if(argc != 2) {
        n = 1000000;
    } else {
        n = atoi(argv[1]);
        n = abs(n);
    }
    */

    // read points
    readPoints * rP = new readPoints();
    vector<Point *> * points = rP->getPoints("points.in");
    //vector<Point *> * points = rP->getPoints("test");
    if (points == NULL) {
        delete rP;
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

    // test
    cout << results->size() << " point in convex hull" << endl;
    if(!rP->checkPoints("res.out", *results)) cout << "Incorrect results" << endl;
    else cout << "Correct results" << endl;

    for(int i = 0; i < results->size(); ++i) cout << *(results->at(i)) << endl;

    // cleanup
    for(size_t i = 0; i < points->size(); ++i) delete points->at(i);
    delete rP;
    delete qH;
    delete points;
    return 0;
}