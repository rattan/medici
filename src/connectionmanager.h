#pragma once

#include <map>
#include <string>

#include "tcpclient.h"
#include "tcpsocket.h"
#include "configmanager.h"
#include "uuid.h"

namespace med {

class ConnectionManager {
    static const std::string TAG;
    std::map<Uuid, TcpSocket> connections;
public:
    void addConnection(Uuid uuid, TcpSocket socket);
    void removeConnection(Uuid uuid);
    void connectToConfigConnection();
    
};

}
