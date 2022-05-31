#include "tcpsocket.h"

TcpSocket::TcpSocket(SOCKET socket): _socket(socket) {
}

void TcpSocket::setOnReceiveListener(std::function<void(char*, int)> listener) {
    bool receiveThreadTrigger = receiveListener.load();
    this->receiveListener.store(listener);

    if(receiveThreadTrigger) {
        this->receiveThread = std::thread([&](){
        this->_buffer = new char[this->bufferSize];
            while(_socket != 0) {
                int receivedSize = recv(this->_socket, this->_buffer, this->bufferSize, 0);
                if(receivedSize != SOCKET_ERROR) {
                    this->receiveListener.l oad()(this->_buffer, receivedSize);
                    if(receivedSize == this->bufferSize && this->bufferSize < INT_MAX) {
                        delete this->_buffer;
                        this->bufferSize <<= 1;
                        this->_buffer = new char[this->bufferSize];
                    }
                }
            }
        })
    }
}

void TcpSocket::send(const char* buffer, int size) const {
    sock_send(_socket, buffer, size, 0);
}
void TcpSocket::close() {
    closesocket(_socket);
#ifdef _WIN32
    WSACleanup();
#endif
delete this->_buffer;
}