#pragma once
#include <sockpp/tcp_connector.h>
#include <commands/MultiThreadCommandContainer.hpp>
#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <mutex>

class TcpClient
{
    private:
    const in_port_t port;
    const std::string host;
    bool shouldStop = false;
    sockpp::tcp_connector conn;

    void read_thr(sockpp::tcp_socket rdSock);
    void write_thr(sockpp::tcp_socket wrSock);

    public:
    void startConnection();
    void write(const std::string& msg);
    ~TcpClient();
};
