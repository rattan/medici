#include "tcpclient.h"

TcpSocket TcpClient::connect(const char* ipAddress, u_short port) {

    struct addrinfo hints, *result = nullptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    char portStr[6]{ 0 };
    _itoa_s(port, portStr, 10);
    int iRes = getaddrinfo(ipAddress, portStr, &hints, &result);
    if(iRes != 0) {
        throw std::exception("getaddrinfo fail.");
    }

    SOCKET clientSocket = INVALID_SOCKET;
    for(struct addrinfo *p = result; p != nullptr; p = p->ai_next) {
        clientSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (INVALID_SOCKET == clientSocket) {
            throw std::exception("Invalid socket.");
        }

        iRes = sock_connect(clientSocket, p->ai_addr, (int)p->ai_addrlen);
        if(iRes == SOCKET_ERROR) {
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);
    if(iRes == SOCKET_ERROR) {
        throw std::exception("Unable to connect to server");
    }

    std::cout << "Connect to server " << ipAddress << "[" << port << "]" << std::endl;
    return TcpSocket(clientSocket);
}