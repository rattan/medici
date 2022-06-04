#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class WSInitializer {
    friend class TcpClient;
    friend class TcpServer;
private:
    bool init = false;
    WSInitializer();
    ~WSInitializer();
};

int(*const sock_connect)(SOCKET, const sockaddr*, int) = connect;
int(*const sock_send)(SOCKET, const char*, int, int) = send;
int(*const sock_listen)(SOCKET, int) = listen;
int(*const sock_receive)(SOCKET, char*, int, int) = recv;
#endif

#ifdef __linux__
	#include <fcntl.h>
	#include <errno.h>
	#include <string.h>  // strlen()
	#include <strings.h> // bzero()
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <arpa/inet.h>
	#include <pthread.h>
	#include <signal.h>
	#include <poll.h>

	#define INVALID_SOCKET    -1
	#define SOCKET_ERROR      -1
	#define ZeroMemory        bzero
	#define closesocket       close
	#define WSAGetLastError() errno
	#define WSAEWOULDBLOCK    EWOULDBLOCK
	#define TRUE              1
	#define FALSE             0

	typedef int                SOCKET;
	typedef struct sockaddr    SOCKADDR;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef fd_set             FD_SET;
	typedef int                BOOL;
	typedef struct pollfd      WSAPOLLFD;

    int(*const sock_connect)(int, const sockaddr*, socklen_t) = connect;
    ssize_t(*const sock_send)(int, const void*, size_t, int) = send;
    int(*const sock_listen)(SOCKET, int) = listen;
    ssize_t(*const sock_receive)(int, void*, size_t, int) = recv;
#endif

#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <exception>

#include <stdlib.h>
#include <stdio.h>



#define DEFAULT_BUFFER_SIZE 1024

class TcpSocket {
    friend class TcpClient;
    friend class TcpServer;
private:
    SOCKET _socket = 0;
    char* _buffer = nullptr;
    int bufferSize = DEFAULT_BUFFER_SIZE;
    std::function<void(char*, int)> receiveListener;
    std::thread receiveThread;
    TcpSocket(SOCKET socket);

    class ReceiveRunner {
        volatile TcpSocket* owner;
    public:
        void setOwner(TcpSocket* o);
        void operator()();
    } runner;
public:
    TcpSocket(TcpSocket&& socket);
    ~TcpSocket();
    void setOnReceiveListener(const std::function<void(char*, int)> &listener);
    void send(const char* buffer, int size) const;
    void close();
};