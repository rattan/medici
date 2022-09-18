#pragma once

#include "tcpserver.h"
#include "log.h"
#include "dependencyset.h"

#include <string>
#include <list>

namespace med {

class ServerManager {
private:
    static const std::string TAG;
    TcpServer broadcastServer;
    TcpServer mediciConnectionServer;
    
public:
    void startMediciConnectionServer();
    void stopMediciConnectionServer();
    void startBroadcastingServer();
    void stopBroadCastingServer();
};

}
