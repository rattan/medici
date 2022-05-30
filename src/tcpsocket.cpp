#include "tcpsocket.h"

TcpSocket::TcpSocket() {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "winsock init error. " << wsa.wVersion << std::endl;
    }
#endif
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == _socket) {
        std::cerr << "invalid socket error." << std::endl;
    }
}

TcpSocket::~TcpSocket() {
    closesocket(_socket);
#ifdef _WIN32
    WSACleanup();
#endif
}