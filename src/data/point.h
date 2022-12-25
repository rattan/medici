#pragma once

#include <cmath>
namespace med {

class Point {
    int _x, _y;
public:
    Point();
    Point(int y, int x);
    int x() const;
    int y() const;
    
    void moveTo(int y, int x);
    void moveTo(Point other);
    unsigned int distance(const Point& other) const;
    Point operator+(Point others);
};

}
