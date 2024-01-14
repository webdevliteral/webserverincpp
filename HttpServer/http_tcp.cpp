#include "http_tcp.h"

namespace HTTP
{    
    const int BUFFER_SIZE = 30720;

    TcpServer::TcpServer(std::string endpoint, int port) : 
    m_endpoint(endpoint), m_port(port), m_socket(), 
    m_new_socket(), m_incomingMessage(), m_socketAddress(), 
    m_socketAddress_len(sizeof(m_socketAddress))
    //, m_serverMessage(buildResponse())
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_endpoint.c_str());

        if (startServer() != 0)
        {
            std::ostringstream ss;
            ss << "Failed to start server with PORT: " << ntohs(m_socketAddress.sin_port);
            Log::Debug::Message(ss.str());
        }
    }    
    
    TcpServer::~TcpServer()
    {
        closeServer();
    }

    int TcpServer::startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        
        if (m_socket < 0)
        {
            Log::Debug::ExitWithError("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
        {
            Log::Debug::ExitWithError("Cannot connect socket to address");
            return 1;
        }

        return 0;
    }

    void TcpServer::closeServer()
    {
        close(m_socket);
        close(m_new_socket);
        Log::Debug::Message("Socket closed successfully. Exiting program with code 0.");
        exit(0);
    }

    void TcpServer::startListen()
    {
        if (listen(m_socket, 20) < 0)
        {
            Log::Debug::ExitWithError("Failed to listen on socket. Exiting.");
        }
        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: " 
            << inet_ntoa(m_socketAddress.sin_addr) 
            << " PORT: " << ntohs(m_socketAddress.sin_port) 
            << " ***\n\n";
        Log::Debug::Message(ss.str());

        int bytesReceived;

        while (true)
        {
            //TODO: stylize waiting message in the console
            Log::Debug::Message("Awaiting a connection...");
            acceptConnection(m_new_socket);

            //create a buffer
            char buffer[BUFFER_SIZE] = {0};
            //read bytes from the socket
            bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE);
            if(bytesReceived < 0)
            {
                Log::Debug::ExitWithError("Failed to read bytes from client.");
            }

            //we manage to read the bytes, continue
            std::ostringstream ss;
            ss << "Incoming request";
            Log::Debug::Message(ss.str());

            //respond
            sendResponse();

            //make sure to close the socket!!!
            close(m_new_socket);
        }
    }

    void TcpServer::acceptConnection(int &new_socket)
    {
        new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, 
                            &m_socketAddress_len);
        if (new_socket < 0)
        {
            std::ostringstream ss;
            ss << 
            "Server failed to accept incoming connection from ADDRESS: " 
            << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " 
            << ntohs(m_socketAddress.sin_port);
            Log::Debug::ExitWithError(ss.str());
        }
    }

    std::string TcpServer::buildResponse()
    {
        std::ostringstream ss;
        //TODO: serve from a file
        //TODO: serve multiple files dynamically
        //std::string htmlFile = "<!DOCTYPE html><html><body><h1>Hello! This text is inside an H1 tag and this is being server on a simple C++ http server.echo $?</h1></body></html>";
        std::ifstream htmlFile ("index.html"); //this is a hack. TODO: parse HTML files (big difficult)
        std::string rawHtml;
        std::string line; 

        while(std::getline(htmlFile, line))
        {
            rawHtml += line;
        }

        //set headers + contents
        ss << "HTTP/1.1 200 OK \nContent-Type: text/html\nContent-Length: " << rawHtml.size() << "\n\n" << rawHtml;
        return ss.str();
    }

    void TcpServer::sendResponse()
    {
        long bytesSent;

        //build a response to send
        m_serverMessage = buildResponse();

        //not sure if c_str is correct but pretty sure I want the pointer
        bytesSent = write(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size());

        //validate any response being sent
        if(bytesSent == m_serverMessage.size())
        {
            Log::Debug::Message("Server successfully sent a response to the client.");
        }
        else 
        {
             Log::Debug::Message("Error sending a response to the client.");
        }
    }

    
} // namespace http