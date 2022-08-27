#pragma once

#include <string>

#include "tcpsocket.h"
#include "log.h"

namespace med {

class TcpClient {
private:
    static const std::string TAG;
public:
    TcpSocket connect(const std::string ipAddress, u_short port);
};

}
