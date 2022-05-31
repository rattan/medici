#include "tcpclient.h"

TcpClient::TcpClient() {
    #ifdef _WIN32
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            std::cerr << "winsock init error. " << wsa.wVersion << std::endl;
        }
    #endif
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (INVALID_SOCKET == clientSocket) {
            std::cerr << "invalid socket error." << std::endl;
        }
}

TcpSocket TcpClient::connect(const char* ipAddress, u_short port) {
    SOCKADDR_IN serverAddr;
    ZeroMemory(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.S_un.S_addr = inet_addr(ipAddress);
    serverAddr.sin_port = htons(port);
    int connectResult = sock_connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (SOCKET_ERROR == connectResult) {
        std::cerr << "connect error. " << std::endl;
    }
    return TcpSocket(clientSocket);
}