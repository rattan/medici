#include "tcpclient.h"

#ifdef _WIN32
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#endif

namespace med {

const std::string TcpClient::TAG = "TcpClient";

TcpSocket TcpClient::connect(const std::string ipAddress, u_short port) {
    SOCKET clientSocket = INVALID_SOCKET;
#ifdef _WIN32
    static WSInitializer initializer;
    struct addrinfo hints, *result = nullptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    char portStr[6]{ 0 };
    _itoa_s(port, portStr, 10);
    int iRes = getaddrinfo(ipAddress.c_str(), portStr, &hints, &result);
    if(iRes != 0) {
        throw std::runtime_error("getaddrinfo fail.");
    }

    for(struct addrinfo *p = result; p != nullptr; p = p->ai_next) {
        clientSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (INVALID_SOCKET == clientSocket) {
            throw std::runtime_error("Invalid socket.");
        }

        iRes = ::connect(clientSocket, p->ai_addr, (int)p->ai_addrlen);
        if(iRes == SOCKET_ERROR) {
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if(iRes == SOCKET_ERROR) {
        throw std::runtime_error("Unable to connect to server");
    }
#endif
    
#if defined __APPLE__ || defined __linux__
    clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    SOCKADDR_IN serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    serverAddr.sin_port = htons(port);
    int connectResult = ::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (SOCKET_ERROR == connectResult) {
        throw std::runtime_error("Unable to connect to server");
    }
#endif

    Log::i(TAG, "Connect to server " + ipAddress + "[" + std::to_string(port) + "]");
    return TcpSocket(clientSocket);
}

}
