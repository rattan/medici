#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
namespace med {
class WSInitializer {
    friend class TcpClient;
    friend class TcpServer;
    friend class TcpSocket;
private:
    static bool init;
    WSInitializer();
    ~WSInitializer();
};
}
#endif

#if defined __APPLE__ || defined __linux__
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
    #include <netinet/in.h>
    #include <netdb.h>
    #include <unistd.h>

    #define INVALID_SOCKET (SOCKET)(~0)
    #define SOCKET_ERROR (-1)

    #define SOCKET int
    typedef struct sockaddr    SOCKADDR;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef fd_set             FD_SET;
    typedef int                BOOL;
    typedef struct pollfd      WSAPOLLFD;
#endif

#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include <stdexcept>
#include <climits>

#include <stdlib.h>
#include <stdio.h>




#define DEFAULT_BUFFER_SIZE 1024
#define BROADCAST_PORT 46470
#define CONNECTION_PORT 46471

namespace med {

class TcpSocket {
    friend class TcpClient;
    friend class TcpServer;
private:
    SOCKET _socket = 0;
    std::function<void(char*, int)> receiveListener;
    TcpSocket(SOCKET socket);
    class ReceiveRunner {
        TcpSocket* _owner = nullptr;
        std::thread receiveThread;
    public:
        ReceiveRunner(TcpSocket* owner);
        void run();
    } *runner = nullptr;
public:
    TcpSocket(TcpSocket&& socket);
    void setOnReceiveListener(const std::function<void(char*, int)> listener);
    void send(const char* buffer, int size) const;
    void close();
    
    static std::string hostName();
    static std::string hostIp();
};

}
