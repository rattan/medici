#pragma once

#include <cstddef>
#include <vector>

namespace med {

class Packet {
public:
    enum class Index: short {
        CONFIG = 0x0001, 
        DISPLAY = 0x0002,
        MOUSE_MOVE = 0x0010,
        MOUSE_BUTTON = 0x0011,
        LIMIT = 0x7FFF
    };
    virtual Index packetIndex() const = 0;
    virtual std::vector<std::byte> boxing() const = 0;
    virtual void unboxing(std::vector<std::byte> dataStream) = 0;
};

}
