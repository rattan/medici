#include "connectionmanager.h"

namespace med {

const std::string ConnectionManager::TAG = "ConnectionManager";

void ConnectionManager::addConnection(Uuid uuid, TcpSocket socket) {
    this->connections.insert(std::pair<Uuid, TcpSocket>(uuid, std::move(socket)));
}

void ConnectionManager::removeConnection(Uuid uuid) {
    this->connections.erase(uuid);
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
