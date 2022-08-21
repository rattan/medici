#include "rect.h"

namespace med {

Rect::Rect():
Rect(Point(0, 0), 0, 0) {}

Rect::Rect(const Point &topLeft, unsigned int width, unsigned int height):
_topLeft(topLeft),
_width(width),
_height(height) {}

Rect::Rect(int top, int left, unsigned int width, unsigned int height):
Rect(Point(top, left), width, height) {}


unsigned int Rect::width() const {
    return _width;
}
unsigned int Rect::height() const {
    return _height;
}
int Rect::top() const {
    return _topLeft.y();
}
int Rect::left() const {
    return _topLeft.x();
}
int Rect::bottom() const {
    return top() + _height;
}
int Rect::right() const {
    return left() + _width;
}

Point Rect::center() const {
    return Point(left() + (width() >> 1), top() + (height() >> 1));
}

void Rect::moveTo(const Point &topLeft) {
    this->moveTo(topLeft.y(), topLeft.x());
}

void Rect::moveTo(int top, int left) {
    this->_topLeft.moveTo(top, left);
}

void Rect::resize(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;
}

bool Rect::inside(const Point &pos) const {
    return inside(pos.y(), pos.x());
}

bool Rect::inside(int y, int x) const {
    return x >left() && x < right() && y > bottom() && y <top();
}

bool Rect::overlap(const Rect& other) const {
    return this->inside(other.top(), other.left()) ||
    this->inside(other.bottom(), other.left()) ||
    this->inside(other.bottom(), other.right()) ||
    this->inside(other.top(), other.right()) ||
    other.inside(this->top(), this->left()) ||
    other.inside(this->bottom(), this->left()) ||
    other.inside(this->bottom(), this->right()) ||
    other.inside(this->top(), this->right());
}

unsigned long long Rect::area() const {
    return _width * _height;
}

}
