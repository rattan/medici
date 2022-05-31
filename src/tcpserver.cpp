#include "tcpserver.h"

TcpServer::TcpServer() {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "winsock init error. " << wsa.wVersion << std::endl;
    }
#endif
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == listenSocket) {
        std::cerr << "invalid socket error." << std::endl;
    }
}

void TcpServer::listen(u_short port) {
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    int bindResult = bind(listenSocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
    if (SOCKET_ERROR == bindResult) {
        std::cerr << "bind error. " << std::endl;
    }

    int listenResult = sock_listen(listenSocket, SOMAXCONN);
	if (listenResult == SOCKET_ERROR) {
        std::cerr << "listen error. " << std::endl;
    }
    while(true) {
        SOCKADDR_IN clientAddres;
        int addressLength = sizeof(clientAddres);
        SOCKET clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddres, &addressLength);
    }
}