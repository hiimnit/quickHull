//
// Created by fsoukup on 16.10.2016.
//

#include "readPoints.h"

vector<Point *> * readPoints::getPoints(string file) {
    vector<Point *> * res = new vector<Point *>();

    if(file == "test") {
        res->push_back(new Point(-5, 0));
        res->push_back(new Point(0, -5));
        res->push_back(new Point(5, 0));
        res->push_back(new Point(0, 5));
        res->push_back(new Point(-4, 3));
        res->push_back(new Point(-4, -3));
        res->push_back(new Point(4, 3));
        res->push_back(new Point(4, -3));
        res->push_back(new Point(3, 4));
        res->push_back(new Point(3, -4));
        res->push_back(new Point(-3, 4));
        res->push_back(new Point(-3, -4));
        res->push_back(new Point(1, 1));
        res->push_back(new Point(-1, 1));
        res->push_back(new Point(1, -1));
        res->push_back(new Point(-1, -1));
        res->push_back(new Point(0, 0));
        res->push_back(new Point(4, 4));
        return res;
    }

    fstream fs(file, fstream::in);
    char line[256];
    int number;
    float x, y;

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

bool cmp(Point* left, Point* right) {
    if (left->x == right->x) return left->y < right->y;
    return left->x < right->x;
}

bool readPoints::checkPoints(string file, vector<Point *> &myResult) {
    int number;
    float x, y;
    fstream fs(file, fstream::in);
    if(!fs.is_open()) {
        cout << "Failed to open " << file << endl;
        return false;
    }

    fs >> number; // reading dimension number
    fs >> number; // reading points number

    if(number != myResult.size()) {
        fs.close();
        return false;
    }

    vector<Point *> * res = new vector<Point *>();
    while(number-- > 0) {
        fs >> x;
        fs >> y;
        res->push_back(new Point(x, y));
    }


    if(res->size() != myResult.size()) {
        fs.close();
        for(int i = 0; i < res->size(); ++i) delete res->at(i);
        delete res;
        return false;
    }


    sort(myResult.begin(), myResult.end(), cmp);
    sort(res->begin(), res->end(), cmp);



    for(int i = 0; i < myResult.size(); ++i) {
        cout << "    read : " << *(res->at(i)) << endl;
        cout << "computed : " << *(myResult.at(i)) << endl;
        if (myResult.at(i)->x != res->at(i)->x || myResult.at(i)->y != res->at(i)->y) {
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

