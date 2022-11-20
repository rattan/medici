#pragma once

#include <cstddef>
#include <vector>

namespace med {

class Packet {
public:
    enum class Index: short {
        CONFIG = 0x0001, 
        DISPLAY = 0x0002,
        MOUSE_EVENT = 0x0010,
        KEYBOARD_EVENT = 0x0011,
        LIMIT = 0x7FFF
    };
    
    virtual Index packetIndex() const = 0;
    virtual std::vector<std::byte> boxing() const = 0;
    virtual void unboxing(std::vector<std::byte> dataStream) = 0;
};

}
