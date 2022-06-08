#include "tcpserver.h"

TcpServer::~TcpServer() {
    //if (this->listenThread) {
    //    this->listenThread->join();
    //    delete this->listenThread;
    //}
}

void TcpServer::listen(u_short port, const std::function<void(const TcpSocket)> &listener) {
    if (this->listenSocket != INVALID_SOCKET) {
        throw std::runtime_error("TcpServer already listening.");
    }

#ifdef _WIN32
    static WSInitializer initializer;
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
        throw std::runtime_error("getaddrinfo fail.");
    }

    this->listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (INVALID_SOCKET == listenSocket) {
        freeaddrinfo(result);
        throw std::runtime_error("Invalid socket error.");
    }
    
    int option = 1;
    setsockopt(this->listenSocket, SOL_SOCKET, SO_REUSEADDR, (char*) & option, sizeof(option));

    int bindResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (SOCKET_ERROR == bindResult) {
        freeaddrinfo(result);
        closesocket(listenSocket);
        throw std::runtime_error("Bind error.");
    }
    freeaddrinfo(result);
#endif
    
#if defined __APPLE__ || defined __linux__
    this->listenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    int option = 1;
    setsockopt(this->listenSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr= INADDR_ANY;
 
    if (bind(this->listenSocket, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        throw std::runtime_error("Bind Error.");
    }
#endif

    int listenResult = sock_listen(listenSocket, SOMAXCONN);
	if (listenResult == SOCKET_ERROR) {
        throw std::runtime_error("Listen error.");
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
    if (this->listenSocket != INVALID_SOCKET) {
        #ifdef _WIN32
        shutdown(this->listenSocket, SD_BOTH);
        closesocket(this->listenSocket);
        #endif
        #if defined __linux__ || __APPLE__
        shutdown(this->listenSocket, SHUT_RDWR);
        #endif
    } else {
        throw std::runtime_error("Listen socket already closed.");
    }
}
