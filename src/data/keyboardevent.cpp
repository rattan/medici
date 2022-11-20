#include "keyboardevent.h"

namespace med {


KeyboardEvent::KeyboardEvent(int key, int flag) :Event(Type::KEYBOARD), _key(key), _flag(flag) {}

int KeyboardEvent::key() const {
    return this->_key;
}
int KeyboardEvent::flag() const {
    return this->_flag;
}


Packet::Index KeyboardEvent::packetIndex() const {
    return Packet::Index::KEYBOARD_EVENT;
}

std::vector<std::byte> KeyboardEvent::boxing() const {
    std::vector<std::byte> result(sizeof(KeyboardEvent));
    std::byte* target = reinterpret_cast<std::byte*>(const_cast<int*>(&this->_key));
    std::copy_n(target, sizeof(int), std::back_inserter(result));
    target = reinterpret_cast<std::byte*>(const_cast<int*>(&this->_flag));
    std::copy_n(target, sizeof(int), std::back_inserter(result));
    return result;
}

void KeyboardEvent::unboxing(std::vector<std::byte> dataStream) {
    int k = 0, f = 0;
    std::copy_n(dataStream.data(), sizeof(int), reinterpret_cast<std::byte*>(&k));
    std::copy_n(dataStream.data() + sizeof(int), sizeof(int), reinterpret_cast<std::byte*>(&f));
    new (this)KeyboardEvent(k, f);
}

}
