#include "tcpsocket.h"

class TcpClient {
private:
    SOCKET clientSocket;
public:
    TcpClient();
    TcpSocket connect(const char* ipAddress, u_short port);
};