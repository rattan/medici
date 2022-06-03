#pragma once

#include "tcpsocket.h"

class TcpClient {
private:
public:
    TcpSocket connect(const char* ipAddress, u_short port);
};