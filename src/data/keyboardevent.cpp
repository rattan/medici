#include "keyboardevent.h"

namespace med {


KeyboardEvent::KeyboardEvent(int key, int flag) :Event(Type::KEYBOARD), _key(key), _flag(flag) {}

int KeyboardEvent::key() const {
    return this->_key;
}
int KeyboardEvent::flag() const {
    return this->_flag;
}

}
