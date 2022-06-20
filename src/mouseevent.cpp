#include "mouseevent.h"

MouseEvent::MouseEvent(Point moveXY, int button) :Event(Type::MOUSE), _moveXY(moveXY), _button(button) {}

const Point& MouseEvent::moveXY() const {
    return this->_moveXY;
}
const int MouseEvent::moveX() const {
    return this->_moveXY.x();
}
const int MouseEvent::moveY() const {
    return this->_moveXY.y();
}
const int MouseEvent::button() const {
    return this->_button;
}