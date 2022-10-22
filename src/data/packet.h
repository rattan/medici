#pragma once

#include <cstddef>
#include <vector>

#define REQUEST 0x8000
#define PACKET_INDEX_
#define PACKET_INDEX_CONFIG 1

#define PACKET_INDEX_MOUSE_MOVE 16
#define PACKET_INDEX_MOUSE_BUTTON 17

namespace med {

class Packet {
public:
    virtual short packetIndex() = 0;
    virtual std::vector<std::byte> boxing() = 0;
    virtual void unboxing(std::vector<std::byte> dataStream) = 0;
public:
};

}
