#include "tcpsocket.h"

#include <thread>

class TcpServer: public TcpSocket {
    private:
    void acceptWorker();
    public:
    TcpServer(u_short port);
};