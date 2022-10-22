#pragma once

#include "../tcp/tcpserver.h"
#include "../util/log.h"

#include <string>
#include <list>
#include <functional>

namespace med {

class ServerManager {
private:
    static const std::string TAG;
    TcpServer broadcastServer;
    TcpServer mediciConnectionServer;
    
public:
    void startMediciConnectionServer(const std::function<void(TcpSocket)> onListenSocket);
    void stopMediciConnectionServer();
    void startBroadcastingServer(const std::function<void(TcpSocket)> onListenSocket);
    void stopBroadCastingServer();
};

}
