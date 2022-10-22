#include "servermanager.h"

namespace med {

const std::string ServerManager::TAG = "ServerManager";

void ServerManager::startMediciConnectionServer(const std::function<void(TcpSocket)> onListenSocket) {
    if(!mediciConnectionServer.isListening()) {
        mediciConnectionServer.listen(CONNECTION_PORT, onListenSocket);
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

void ServerManager::startBroadcastingServer(const std::function<void(TcpSocket)> onListenSocket) {
    if(!broadcastServer.isListening()) {
        broadcastServer.listen(BROADCAST_PORT, onListenSocket);
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
