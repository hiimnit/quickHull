#include <iostream>
#include "quickHull.h"
#include "randomizePoints.h"

using namespace std;

int main(int argc, char* argv[]) {
    int n;
    if(argc != 2) {
        n = 1000000;
    } else {
        n = atoi(argv[1]);
        n = abs(n);
    }
    cout << "#points : " << n << endl;

    randomizePoints * rP = new randomizePoints();
    vector<Point *> * points = rP->getPoints(50000);

    // cast pro mereni
    quickHull * qH = new quickHull(*points);
    vector<Edge *> resultEdges = qH->run();
    // </> cast pro mereni

    // testloop
    int lastdir = -1;
    for(auto e : resultEdges) {
        // e->Print();

        if (lastdir > e->direction()) {
            cout << "Err" << endl;
            e->Print();
        }
        lastdir = e->direction();
    }

    cout << "done" << endl;

    for(size_t i = 0; i < points->size(); ++i) delete points->at(i);
    delete rP;
    delete qH;
    delete points;
    return 0;
}