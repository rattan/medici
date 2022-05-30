#include "tcpsocket.h"

class TcpClient: public TcpSocket {
public:
    TcpClient(const char* ipAddress, u_short port);
};