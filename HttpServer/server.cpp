#include "http_tcp.h"
#include "files.h"

int main()
{
    HTTP::TcpServer server = HTTP::TcpServer("0.0.0.0", 8080);
    server.startListen();
    return 0;
}