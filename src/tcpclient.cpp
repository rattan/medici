#include "tcpclient.h"

TcpClient::TcpClient(const char* ipAddress, u_short port): TcpSocket() {
    SOCKADDR_IN serverAddr;
    ZeroMemory(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.S_un.S_addr = inet_addr(ipAddress);
    serverAddr.sin_port = htons(port);
    int connectResult = connect(_socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (SOCKET_ERROR == connectResult) {
        std::cerr << "connect error. " << std::endl;
    }
}