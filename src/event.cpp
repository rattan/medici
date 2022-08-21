#include "event.h"

namespace med {


Event::Event(Type type) : _type(type) {}

Event::Type Event::type() const {
    return this->_type;
}

}
