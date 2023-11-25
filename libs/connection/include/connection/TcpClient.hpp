#pragma once
#include <sockpp/tcp_connector.h>
#include <commands/MultiThreadCommandContainer.hpp>
#include <memory>
#include <condition_variable>

namespace connection
{

using ContainerPtr = std::unique_ptr<MultiThreadCommandContainer>;

class TcpClient
{
    private:
    ContainerPtr received_commands;
    ContainerPtr commands_to_send;
    
    void senderThread(sockpp::tcp_socket socket);
    void receiverThread(sockpp::tcp_socket socket);
    
    std::condition_variable send_condition;
    std::condition_variable receive_condition;

    public:
    TcpClient(ContainerPtr receive_container, ContainerPtr send_container);
    bool startConnection(const std::string& host, const in_port_t& port);
    void sendCommand(const std::string& command);
    bool popCommand(std::string& command);
    std::string popCommandWait();

};

};

