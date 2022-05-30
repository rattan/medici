#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
#endif

#ifdef __linux__
	#include <unistd.h>
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
#endif

#include <iostream>
#include <string>
#include <functional>

#include <stdlib.h>
#include <stdio.h>

class TcpSocket {
protected:
    SOCKET _socket = 0;
    SOCKADDR_IN _serveraddr;
    TcpSocket();
    TcpSocket(SOCKET socket): _socket(socket) {}
public:
    ~TcpSocket();

    void send(const BYTE* buffer, int size);
    void receive(std::function<void(BYTE*, int)>);
};