#include "tcpsocket.h"

#ifdef _WIN32
WSInitializer::WSInitializer() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "winsock init error. " << wsa.wVersion << std::endl;
    } else {
        std::cout << "winsock init " << wsa.wVersion << std::endl;
    }
}

WSInitializer::~WSInitializer() {
    WSACleanup();
}
#endif

TcpSocket::TcpSocket(SOCKET socket): _socket(socket) {}

void TcpSocket::setOnReceiveListener(std::function<void(char*, int)> &listener) {
    if(_socket == 0) {
        throw std::exception("Can't receive. TcpSocket not avaliable.");
    }

    bool receiveThreadTrigger = false;
    if(receiveListener.load()) {
        receiveThreadTrigger = true;
    }
    this->receiveListener.store(listener);

    if(receiveThreadTrigger) {
        this->receiveThread = std::thread([&](){
            this->_buffer = new char[this->bufferSize];
            while(_socket) {
                int receivedSize = recv(this->_socket, this->_buffer, this->bufferSize, 0);
                if(receivedSize != SOCKET_ERROR) {
                    this->receiveListener.load()(this->_buffer, receivedSize);
                    if(receivedSize == this->bufferSize && this->bufferSize < INT_MAX) {
                        delete this->_buffer;
                        this->bufferSize <<= 1;
                        this->_buffer = new char[this->bufferSize];
                    }
                }
            }
            std::cout<<"receive end"<<std::endl;
        });
    }
}

void TcpSocket::send(const char* buffer, int size) const {
    if(_socket) {
        sock_send(_socket, buffer, size, 0);
    } else {
        throw std::exception("Can't send. TcpSocket not avaliable.");
    }
}

void TcpSocket::close() {
    if(_socket) {
        closesocket(_socket);
        delete this->_buffer;
    } else {
        throw std::exception("TcpSocket already closed");
    }
}