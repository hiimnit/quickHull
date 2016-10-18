//
// Created by fsoukup on 16.10.2016.
//

#ifndef QUICKHULL_POINT_H
#define QUICKHULL_POINT_H


class Point {
    int x;
    int y;
public:
    Point(int x, int y);
    virtual ~Point();
    int getX() const;
    int getY() const;
};


#endif //QUICKHULL_POINT_H
