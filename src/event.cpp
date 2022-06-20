#include "event.h"

Event::Event(Type type) : _type(type) {}

Event::Type Event::type() const {
    return this->_type;
}