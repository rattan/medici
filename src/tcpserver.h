#pragma once

#include "tcpsocket.h"

class TcpServer {
private:
    SOCKET listenSocket = 0;
    std::function<void(TcpSocket)> acceptListener;
    std::thread *listenThread = nullptr;
public:
    ~TcpServer();
    void listen(u_short port, const std::function<void(TcpSocket)> &listener);
    void close();
};
