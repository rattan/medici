#include "tcpsocket.h"

#ifdef _WIN32
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

void TcpSocket::ReceiveRunner::setOwner(TcpSocket* o) {
    this->owner = o;
}
void TcpSocket::ReceiveRunner::operator()() {
    owner->_buffer = new char[owner->bufferSize];
    while (owner->_socket != INVALID_SOCKET) {
        int receivedSize = sock_receive(owner->_socket, owner->_buffer, owner->bufferSize, 0);
        if (receivedSize != SOCKET_ERROR) {
            const_cast<TcpSocket*>(owner)->receiveListener(owner->_buffer, receivedSize);
            if (receivedSize == owner->bufferSize && owner->bufferSize < INT_MAX) {
                delete owner->_buffer;
                owner ->bufferSize <<= 1;
                owner->_buffer = new char[owner->bufferSize];
            }
        }
    }
    std::cout << "receive end" << std::endl;
    delete[] owner->_buffer;
}

TcpSocket::TcpSocket(SOCKET socket) : _socket(socket) {
    this->runner.setOwner(this);
}

TcpSocket::TcpSocket(TcpSocket&& socket) {
    this->_socket = socket._socket;
    this->_buffer = socket._buffer;
    this->bufferSize = socket.bufferSize;
    std::swap(this->receiveListener, socket.receiveListener);
    this->receiveThread = std::move(socket.receiveThread);
    this->runner = std::move(socket.runner);
    this->runner.setOwner(this);
    socket._socket = INVALID_SOCKET;
    socket._buffer = nullptr;
    socket.runner.setOwner(nullptr);
}

TcpSocket::~TcpSocket() {
    //if (this->receiveThread) {
    //    delete this->receiveThread;
    //}
}

void TcpSocket::setOnReceiveListener(const std::function<void(char*, int)> &listener) {
    if(_socket == 0) {
        throw std::exception("Can't receive. TcpSocket not avaliable.");
    }

    bool receiveThreadTrigger = false;
    if(!receiveListener) {
        receiveThreadTrigger = true;
    }
    this->receiveListener = listener;

    if(receiveThreadTrigger) {
        this->receiveThread = std::move(std::thread(runner));
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
    } else {
        throw std::exception("TcpSocket already closed");
    }
}