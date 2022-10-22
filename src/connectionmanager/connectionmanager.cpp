#include "connectionmanager.h"

namespace med {

const std::string ConnectionManager::TAG = "ConnectionManager";

void ConnectionManager::addConnection(TcpSocket socket, Uuid uuid) {

    socket.setOnReceiveListener([&](char* buffer, int size){

    });

    if(uuid == Uuid::nil()) {

    }

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

void ConnectionManager::addBroadCastConnection(TcpSocket socket, Uuid uuid) {
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

// void ConnectionManager::connectToConfigConnection() {
//     for(const auto& connect: ConfigManager::instance().connections()) {
//         if(this->connections.find(connect.uuid()) == this->connections.end()) {
//             Log::i(TAG, "try to connect to " + connect.ipAddress());
//             TcpClient connectClient;
//             try {
//                 addConnection(connect.uuid(), connectClient.connect(connect.ipAddress(), CONNECTION_PORT));
//             } catch (std::runtime_error e) {
//                 Log::e(TAG, "can not connect to " + connect.ipAddress());
//             }
//         }
//     }
// }

    void ConnectionManager::send(Uuid uuid, Packet &packet) {
        auto socket = connections.find(uuid);
        if(socket != this->connections.end()) {
            std::vector<std::byte> body = packet.boxing();
            unsigned short bodySize = 0;
            if (body.size() > 0xFFFF) {
                Log::w("PACKET", std::string("packet size too long ") + std::to_string(body.size()));
                bodySize = 0xFFFF;
            } else {
                bodySize = (unsigned short)body.size();
            }
            int bufferSize = bodySize + 4;
            char *buffer = new char[bufferSize];
            std::copy_n(reinterpret_cast<char*>(&index),2, buffer);
            std::copy_n(reinterpret_cast<char*>(&bodySize),2, buffer+2);
            std::transform(std::begin(body), std::end(body), buffer + 4, [](std::byte b) {
                return (char)b;
            });
            socket->second.send(buffer, bufferSize);
        }
    }

    void ConnectionManager::broadcast(Packet &packet) {
        if(this->connections.empty()) {
            return;
        }

        std::vector<std::byte> body = packet.boxing();
        unsigned short bodySize = 0;
        if (body.size() > 0xFFFF) {
            Log::w("PACKET", std::string("packet size too long ") + std::to_string(body.size()));
            bodySize = 0xFFFF;
        } else {
            bodySize = (unsigned short)body.size();
        }
        int bufferSize = bodySize + 4;
        char *buffer = new char[bufferSize];
        std::copy_n(reinterpret_cast<char*>(&index),2, buffer);
        std::copy_n(reinterpret_cast<char*>(&bodySize),2, buffer+2);
        std::transform(std::begin(body), std::end(body), buffer + 4, [](std::byte b) {
            return (char)b;
        });

        for(auto &socket: this->connections) {
            socket.second.send(buffer, bufferSize);
        }
        delete []buffer;
    }


    Packet& ConnectionManager::streamToPacket(const char * streamBuffer, int* consumeByte) {
        // short index;
        // unsigned short size;
        // std::vector<std::byte> body;
        // std::copy_n(streamBuffer, 2,reinterpret_cast<char*>(&index));
        // std::copy_n(streamBuffer + 2, 2, reinterpret_cast<char*>(&size));
        // std::transform(streamBuffer + 4, streamBuffer + 4 + size, std::back_inserter(body), [](char ch){
        //     return std::byte(ch);
        // });
        // return size + 4;
        return Packet();
    }

}
