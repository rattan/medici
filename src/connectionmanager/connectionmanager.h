#pragma once

#include <map>
#include <string>

#include "../tcp/tcpclient.h"
#include "../tcp/tcpsocket.h"
#include "../data/uuid.h"
#include "../data/packet.h"

namespace med {

class ConnectionManager {
    static const std::string TAG;
    std::map<Uuid, TcpSocket> connections;
    std::map<Uuid, TcpSocket> broadCastConnections;

    // Packet& streamToPacket(const char* streamBuffer, int* consumeByte);
public:
    void addConnection(TcpSocket socket);
    void addBroadCastConnection(TcpSocket socket);
    void removeConnection(Uuid uuid);
    void removeBroadCastConnection(Uuid uuid);
    
    void send(Uuid uuid, Packet &packet);
    void broadcast(Packet &packet);

};

}
