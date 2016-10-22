#include <iostream>
#include "quickHull.h"
#include "randomizePoints.h"

using namespace std;

int main() {
    randomizePoints * rP = new randomizePoints();
    vector<Point *> * points = rP->getPoints(1000);

    quickHull * qH = new quickHull(*points);

    vector<Edge *> resultEdges = qH->execute();

    for(auto e : resultEdges) {
        e->Print();
    }

    // osetrit pripady pro 1, 2, 3 body

    // smazat rP, points, qH, jednotlive Points
    //   - az bude result vector, tak i ten ? ten mozna v destruktoru quickHull
    for(int i = 0; i < points->size(); ++i) delete points->at(i);
    delete rP;
    delete points;
    delete qH;
    return 0;
}