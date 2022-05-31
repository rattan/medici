#include "tcpsocket.h"

class TcpClient: public TcpSocket {
private:
    SOCKET clientSocket;
public:
    TcpClient();
    TcpSocket connect(const char* ipAddress, u_short port);
};