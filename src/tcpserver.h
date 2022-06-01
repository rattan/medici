#include "tcpsocket.h"

#include <thread>

class TcpServer {
    private:
    SOCKET listenSocket = 0;
    std::function<void(TcpSocket)> acceptListener;
    std::thread listenThread;
    public:
    void listen(u_short port, std::function<void(TcpSocket)> &listener);
    void close();
};