#pragma once

#include "tcpsocket.h"

namespace med {

class TcpServer {
private:
    SOCKET listenSocket = INVALID_SOCKET;
    std::function<void(TcpSocket)> acceptListener;
    std::thread *listenThread = nullptr;
public:
    ~TcpServer();
    void listen(u_short port, const std::function<void(TcpSocket)> listener);
    bool isListening();
    void close();
};

}
