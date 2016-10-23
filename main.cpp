#include <iostream>
#include "quickHull.h"
#include "randomizePoints.h"

using namespace std;

int main() {
    randomizePoints * rP = new randomizePoints();


    vector<Point *> * points = rP->getPoints(10000);

    // cast pro mereni
    quickHull * qH = new quickHull(*points);
    vector<Edge *> resultEdges = qH->execute();
    // </> cast pro mereni

    for(auto e : resultEdges) {
        e->Print();
    }

    // osetrit pripady pro 1, 2, 3 body

    for(int i = 0; i < points->size(); ++i) delete points->at(i);
    for(int i = 0; i < resultEdges.size(); ++i) delete resultEdges.at(i);
    delete rP;
    delete points;
    delete qH;
    return 0;
}