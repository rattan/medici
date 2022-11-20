#include "mouseevent.h"

namespace med {


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

Packet::Index MouseEvent::packetIndex() const {
    return Packet::Index::MOUSE_EVENT;
}

std::vector<std::byte> MouseEvent::boxing() const {
    std::vector<std::byte> result(sizeof(MouseEvent));
    std::byte* target = reinterpret_cast<std::byte*>(const_cast<Point*>(&this->_moveXY));
    std::copy_n(target, sizeof(Point), std::back_inserter(result));
    target = reinterpret_cast<std::byte*>(const_cast<int*>(&this->_button));
    std::copy_n(target, sizeof(int), std::back_inserter(result));
    return result;
}

void MouseEvent::unboxing(std::vector<std::byte> dataStream) {
    Point p{0, 0};
    int btn = 0;
    std::copy_n(dataStream.data(), sizeof(Point), reinterpret_cast<std::byte*>(&p));
    std::copy_n(dataStream.data() + sizeof(Point), sizeof(int), reinterpret_cast<std::byte*>(&btn));
    new (this)MouseEvent(p, btn);
}

}
