#pragma once

#include <cstddef>
#include <vector>

#define REQUEST 0x8000
#define PACKET_INDEX_
#define PACKET_INDEX_PING 0
#define PACKET_INDEX_PROTOCOL_VERSION 1
#define PACKET_INDEX_APP_VERSION 2
#define PACKET_INDEX_UUID 3
#define PACKET_INDEX_OS 4
#define PACKET_INDEX_NAME 5
#define PACKET_INDEX_IP_ADDRESS 6
#define PACKET_INDEX_DISPLAY 7
#define PACKET_INDEX_CONFIG 8

#define PACKET_INDEX_MOUSE_MOVE 16
#define PACKET_INDEX_MOUSE_BUTTON 17

namespace med {

class Packet {
    unsigned short packetIndex;
    unsigned short size;
    std::vector<std::byte> body;
public:
};

}
