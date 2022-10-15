#pragma once

#include <map>
#include <string>

#include "../tcp/tcpclient.h"
#include "../tcp/tcpsocket.h"
// #include "../configmanager.h"
#include "../data/uuid.h"

namespace med {

class ConnectionManager {
    static const std::string TAG;
    std::map<Uuid, TcpSocket> connections;
    std::map<Uuid, TcpSocket> broadCastConnections;
public:
    void addConnection(Uuid uuid, TcpSocket socket);
    void addBroadCastConnection(Uuid uuid, TcpSocket socket);
    void removeConnection(Uuid uuid);
    void removeBroadCastConnection(Uuid uuid);
    // void connectToConfigConnection();
    
};

}
