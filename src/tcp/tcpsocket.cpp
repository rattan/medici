#include "tcpsocket.h"

namespace med {

#ifdef _WIN32
bool WSInitializer::init = false;
WSInitializer::WSInitializer() {
    if (this->init == false) {
        this->init = true;
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            std::cerr << "winsock init error. " << wsa.wVersion << std::endl;
        }
        else {
            std::cout << "winsock init " << wsa.wVersion << std::endl;
        }
    }
}

WSInitializer::~WSInitializer() {
    if (this->init) {
        WSACleanup();
        this->init = false;
    }
}
#endif

TcpSocket::ReceiveRunner::ReceiveRunner(TcpSocket* owner): _owner(owner) {}

void TcpSocket::ReceiveRunner::run() {
    new(&receiveThread) std::thread([&]() {
        int bufSize = DEFAULT_BUFFER_SIZE;
        char* buffer = new char[bufSize];
        while (_owner->_socket != INVALID_SOCKET) {
            int receivedSize = ::recv(_owner->_socket, buffer, bufSize, 0);
            if (receivedSize != SOCKET_ERROR) {
                _owner->receiveListener(buffer, receivedSize);
                if (receivedSize == bufSize && bufSize < INT_MAX) {
                    delete[] buffer;
                    bufSize <<= 1;
                    buffer = new char[bufSize];
                }
                if(receivedSize == 0) {
                    break;
                }
            }
        }
        std::cout << "receive end" << std::endl;
        delete[] buffer;
        delete _owner->runner;
        });
}

TcpSocket::TcpSocket(SOCKET socket) : _socket(socket) {
}

TcpSocket::TcpSocket(TcpSocket&& socket)
    : _socket(socket._socket),
    receiveListener(std::move(socket.receiveListener)),
    runner(socket.runner) {
    if(runner) {
        new(runner) ReceiveRunner(this);
    }
    socket._socket = INVALID_SOCKET;
    socket.runner = nullptr;
}

void TcpSocket::setOnReceiveListener(const std::function<void(char*, int)> listener) {
    if(_socket == INVALID_SOCKET) {
        throw std::runtime_error("Can't receive. TcpSocket not avaliable.");
    }

    bool receiveThreadTrigger = false;
    if(!receiveListener) {
        receiveThreadTrigger = true;
    }
    this->receiveListener = listener;

    if(receiveThreadTrigger) {
        runner = new ReceiveRunner(this);
        runner->run();
    }
}

void TcpSocket::send(const char* buffer, int size) const {
    if(_socket != INVALID_SOCKET) {
        ::send(_socket, buffer, size, 0);
    } else {
        throw std::runtime_error("Can't send. TcpSocket not avaliable.");
    }
}

void TcpSocket::close() {
    if(_socket != INVALID_SOCKET) {
        #ifdef _WIN32
        shutdown(this->_socket, SD_BOTH);
        closesocket(this->_socket);
        #endif
        #if defined __linux__ || __APPLE__
        shutdown(this->_socket, SHUT_RDWR);
        #endif
    } else {
        throw std::runtime_error("TcpSocket already closed");
    }
}


std::string TcpSocket::hostName() {
#ifdef _WIN32
    static WSInitializer initializer;
#endif
    char host[256]{ 0 };
    gethostname(host, sizeof(host));
    return std::string(host);
}

std::string TcpSocket::hostIp() {
#ifdef _WIN32
    static WSInitializer initializer;
#endif
    char host[256]{ 0 };
    int hostname = gethostname(host, sizeof(host));
// #ifdef _WIN32
//     struct addrinfo* servinfo;
//     getaddrinfo(host, nullptr, nullptr, &servinfo);
//     char ip[256]{ 0 };
//     inet_ntoa(AF_INET, servinfo, ip, sizeof(ip));
// #endif
// #if defined __APPLE__ || defined __linux__
    struct hostent* host_entry = gethostbyname(host);
    char* ip = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0])); //Convert into IP string
// #endif
    return std::string(ip);
}

}
