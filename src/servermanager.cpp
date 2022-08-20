#include "servermanager.h"

void ServerManager::startBroadcasting() {
    broadcastServer.listen(BROADCAST_PORT, [&](TcpSocket socket){
        
//        this->broadCastSocket.push_back(std::move(socket));
    });
    
}

void ServerManager::stopBroadCasting() {
    
}
