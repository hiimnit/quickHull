#include <iostream>
#include "quickHull.h"
#include "randomizePoints.h"

using namespace std;

int main() {
    randomizePoints * rP = new randomizePoints();
    vector<Point *> * points = rP->getPoints(1000);

    quickHull * qH = new quickHull(*points);


    // smazat rP, points, qH, jednotlive Points
    //   - az bude result vector, tak i ten ? ten mozna v destruktoru quickHull
    for(int i; i < points->size(); ++i) delete points->at(i);
    delete rP;
    delete points;
    delete qH;
    return 0;
}