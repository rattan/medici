#include "tcpclient.h"

TcpSocket TcpClient::connect(const char* ipAddress, u_short port) {
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == clientSocket) {
        std::cerr << "Invalid socket error." << std::endl;
        throw std::exception("Invalid socket error.");
    }

    SOCKADDR_IN serverAddr;
    ZeroMemory(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.S_un.S_addr = inet_addr(ipAddress);
    serverAddr.sin_port = htons(port);
    int connectResult = sock_connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (SOCKET_ERROR == connectResult) {
        std::cerr << "Connect error. " << std::endl;
        throw std::exception("Connect error.");
    }
    return TcpSocket(clientSocket);
}