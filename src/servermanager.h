#pragma once

#include "tcpserver.h"

#include <list>

#define BROADCAST_PORT 46470
#define CONNECTION_PORT 46471


class ServerManager {
private:
    TcpServer broadcastServer;
    std::list<TcpSocket> broadCastSocket;
    TcpServer mediciConnectionServer;
    std::list<TcpSocket> connectedSocket;
    
    
    
public:
    
    void startBroadcasting();
    void stopBroadCasting();
    
    
    
};
