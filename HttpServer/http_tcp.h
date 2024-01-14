#ifndef HTTP_TCP_H
#define HTTP_TCP_H

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <fstream>
#include "Log.h"
#include "files.h"

namespace HTTP
{
    class TcpServer
    {
    public:
        TcpServer(std::string endpoint, int port);
        ~TcpServer();
        void startListen();

    private:
        std::string m_endpoint;
        int m_port;
        int m_socket;
        int m_new_socket;
        long m_incomingMessage;
        struct sockaddr_in m_socketAddress;
        uint m_socketAddress_len;
        std::string m_serverMessage;

        int startServer();
        void closeServer();
        void acceptConnection(int &new_socket);
        std::string buildResponse();
        void sendResponse();
    };
} // namespace HTTP
#endif