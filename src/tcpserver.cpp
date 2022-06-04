#include "tcpserver.h"

TcpServer::~TcpServer() {
    //if (this->listenThread) {
    //    this->listenThread->join();
    //    delete this->listenThread;
    //}
}

void TcpServer::listen(u_short port, const std::function<void(const TcpSocket)> &listener) {
#ifdef _WIN32
    static WSInitializer initializer;
#endif
    if (this->listenSocket != 0) {
        throw std::exception("TcpServer already listening.");
    }

    struct addrinfo hints, *result = nullptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    char portStr[6]{ 0 };
    _itoa_s(port, portStr, 10);
    int iRes = getaddrinfo(nullptr, portStr, &hints, &result);
    if(iRes != 0) {
        throw std::exception("getaddrinfo fail.");
    }

    this->listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (INVALID_SOCKET == listenSocket) {
        freeaddrinfo(result);
        throw std::exception("Invalid socket error.");
    }

    int bindResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (SOCKET_ERROR == bindResult) {
        freeaddrinfo(result);
        closesocket(listenSocket);
        throw std::exception("Bind error.");
    }

    freeaddrinfo(result);

    int listenResult = sock_listen(listenSocket, SOMAXCONN);
	if (listenResult == SOCKET_ERROR) {
        throw std::exception("Listen error.");
    }

    this->acceptListener = listener;

    listenThread = new std::thread([&](){
        while(this->listenSocket) {
            SOCKET clientSocket = accept(this->listenSocket, nullptr, nullptr);
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