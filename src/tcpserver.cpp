#include "tcpserver.h"

void TcpServer::listen(u_short port, std::function<void(TcpSocket)> &listener) {

    if (this->listenSocket != 0) {
        throw std::exception("TcpServer already listening.");
    }

    this->listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == listenSocket) {
        std::cerr << "Invalid socket error." << std::endl;
        throw std::exception("Invalid socket error.");
    }

    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    int bindResult = bind(listenSocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
    if (SOCKET_ERROR == bindResult) {
        std::cerr << "Bind error. " << std::endl;
        throw std::exception("Bind error.");
    }

    int listenResult = sock_listen(listenSocket, SOMAXCONN);
	if (listenResult == SOCKET_ERROR) {
        std::cerr << "Listen error. " << std::endl;
        throw std::exception("Listen error.");
    }

    this->acceptListener = listener;

    listenThread = std::thread([&](){
        while(this->listenSocket) {
            SOCKADDR_IN clientAddres;
            int addressLength = sizeof(clientAddres);
            SOCKET clientSocket = accept(this->listenSocket, (SOCKADDR*)&clientAddres, &addressLength);
            this->acceptListener(TcpSocket(clientSocket));
        }
        std::cout << "listen end [" << port << "]" << std::endl;
    });
}

void TcpServer::close() {
    if (this->listenSocket) {
        closesocket(this->listenSocket);
    } else {
        throw std::exception("Listen socket already closed.");
    }
}