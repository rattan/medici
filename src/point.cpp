#include "point.h"

namespace med{

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
unsigned int Point::distance(const Point& other) const {
    long long width = this->_x - other._x;
    long long height = this->_y - other._y;
    return sqrt(width * width + height * height);
}

}
