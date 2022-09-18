#include "connectionmanager.h"

namespace med {

const std::string ConnectionManager::TAG = "ConnectionManager";

void ConnectionManager::addConnection(Uuid uuid, TcpSocket socket) {
    if(this->connections.find(uuid) != this->connections.end()) {
        std::stringstream logStream;
        logStream<<uuid.toString()<<" already contains connections.";
        Log::w(TAG, logStream.str());
    }
    if(this->broadCastConnections.find(uuid) != this->broadCastConnections.end()) {
        std::stringstream logStream;
        logStream<<uuid.toString()<<" contains broadcast connections. move to connections";
        Log::i(TAG, logStream.str());
        removeBroadCastConnection(uuid);
        this->broadCastConnections.erase(uuid);
    }
    this->connections.insert(std::pair<Uuid, TcpSocket>(uuid, std::move(socket)));
}

void ConnectionManager::removeConnection(Uuid uuid) {
    this->connections.erase(uuid);
}

void ConnectionManager::addBroadCastConnection(Uuid uuid, TcpSocket socket) {
    if(this->broadCastConnections.find(uuid) != this->broadCastConnections.end()) {
        std::stringstream logStream;
        logStream<<uuid.toString()<<" already contains broadcast connections.";
        Log::i(TAG, logStream.str());
    }
    this->broadCastConnections.insert(std::pair<Uuid, TcpSocket>(uuid, std::move(socket)));
}

void ConnectionManager::removeBroadCastConnection(Uuid uuid) {
    this->broadCastConnections.erase(uuid);
}

void ConnectionManager::connectToConfigConnection() {
    for(const auto& connect: ConfigManager::instance().connections()) {
        if(this->connections.find(connect.uuid()) == this->connections.end()) {
            Log::i(TAG, "try to connect to " + connect.ipAddress());
            TcpClient connectClient;
            try {
                addConnection(connect.uuid(), connectClient.connect(connect.ipAddress(), CONNECTION_PORT));
            } catch (std::runtime_error e) {
                Log::e(TAG, "can not connect to " + connect.ipAddress());
            }
        }
    }
}

}
