#pragma once

#include <cmath>

class Point {
    int _x, _y;
public:
    Point(int y, int x);
    int x() const;
    int y() const;
    
    void moveTo(int y, int x);
    unsigned int distance(const Point& other) const;
    
};
