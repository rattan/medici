#include "tcpsocket.h"

#include <thread>

class TcpServer {
    private:
    SOCKET listenSocket;
    std::function<void(TcpSocket)> acceptListener;
    public:
    TcpServer();
    void setOnAcceptListener(std::function<void(TcpSocket)> listener);
    void listen(u_short port);
    void close();
};