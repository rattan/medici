#include "point.h"

namespace med{

Point::Point(): _y(0), _x(0) {}

Point::Point(int y, int x): _y(y), _x(x) {}
int Point::x() const {
    return _x;
}
int Point::y() const {
    return _y;
}

void Point::moveTo(int y, int x) {
    this->_x = x;
    this->_y = y;
}

void Point::moveTo(Point p) {
    moveTo(p.y(), p.x());
}

unsigned int Point::distance(const Point& other) const {
    long long width = this->_x - other._x;
    long long height = this->_y - other._y;
    return sqrt(width * width + height * height);
}

Point Point::operator+(Point others) {
    return Point(this->y() + others.y(), this->x() + others.x());
}

}
