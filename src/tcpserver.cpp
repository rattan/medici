#include "tcpserver.h"

TcpServer::TcpServer(u_short port): TcpSocket() {
    ZeroMemory(&_serveraddr, sizeof(_serveraddr));
    _serveraddr.sin_family = AF_INET;
    _serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    _serveraddr.sin_port = htons(port);

    int bindResult = bind(_socket, (SOCKADDR *)&_serveraddr, sizeof(_serveraddr));
    if (SOCKET_ERROR == bindResult) {
        std::cerr << "bind error. " << std::endl;
    }

    int listenResult = listen(_socket, SOMAXCONN);
	if (listenResult == SOCKET_ERROR) {
        std::cerr << "listen error. " << std::endl;
    }
}

void TcpServer::acceptWorker() {
    while(true) {
        SOCKADDR_IN clientAddres;
        int addressLength = sizeof(clientAddres);
        SOCKET clientSocket = accept(_socket, (SOCKADDR*)&clientAddres, &addressLength);
    }
}