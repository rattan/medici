#pragma once

#include "tcpserver.h"
#include "log.h"

#include <string>
#include <list>

namespace med {

class ServerManager {
private:
    static const std::string TAG;
    TcpServer broadcastServer;
    std::list<TcpSocket> broadCastSocket;
    TcpServer mediciConnectionServer;
    std::list<TcpSocket> connectedSocket;
    
    
    
public:
    void startMediciConnectionServer();
    void stopMediciConnectionServer();
    void startBroadcastingServer();
    void stopBroadCastingServer();
};

}
