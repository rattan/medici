#include "servermanager.h"

namespace med {

const std::string ServerManager::TAG = "ServerManager";

void ServerManager::startMediciConnectionServer() {
    if(!mediciConnectionServer.isListening()) {
        mediciConnectionServer.listen(CONNECTION_PORT, [&](TcpSocket) {
            
        });
        Log::i(TAG, "MediciConnection server listen start");
    } else {
        Log::w(TAG, "MediciConnection server already listening");
    }
}

void ServerManager::stopMediciConnectionServer() {
    if(mediciConnectionServer.isListening()) {
        mediciConnectionServer.close();
    }
}

void ServerManager::startBroadcastingServer() {
    if(!broadcastServer.isListening()) {
        broadcastServer.listen(BROADCAST_PORT, [&](TcpSocket socket){
            this->broadCastSocket.push_back(std::move(socket));
        });
        Log::i(TAG, "Broadcast server listen start");
    } else {
        Log::w(TAG, "Broadcast server already listening");
    }
}

void ServerManager::stopBroadCastingServer() {
    if(broadcastServer.isListening()) {
        broadcastServer.close();
    }
}
}
