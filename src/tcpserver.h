#pragma once

#include "tcpsocket.h"

#include <thread>

class TcpServer {
private:
    SOCKET listenSocket = 0;
    std::function<void(TcpSocket)> acceptListener;
    std::thread *listenThread;
public:
    ~TcpServer();
    void listen(u_short port, const std::function<void(TcpSocket)> listener);
    void close();
};