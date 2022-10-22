#pragma once

#include "../tcp/tcpserver.h"
#include "../util/log.h"
#include "../dependencyset/dependencyset.h"
#include "../connectionmanager/connectionmanager.h"

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
