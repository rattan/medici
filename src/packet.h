#pragma once

#include <cstddef>
#include <vector>

#define REQUEST 0x8000

namespace med {

class Packet {
    unsigned short index;
    unsigned short size;
    std::vector<std::byte> body;
};

}
