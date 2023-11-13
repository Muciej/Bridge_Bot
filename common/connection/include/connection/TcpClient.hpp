#pragma once
#include <sockpp/tcp_connector.h>
#include <commands/MultiThreadCommandContainer.hpp>
#include <memory>
#include <condition_variable>

namespace connection
{

using ContainerPtr = std::unique_ptr<MultiThreadCommandContainer>;

class Sender
{
    ContainerPtr commands_to_send;

    public:
    Sender(ContainerPtr container);

    void operator()();
};

class Receiver
{
    private:
    ContainerPtr received_commands;

    public:
    Receiver(ContainerPtr container);

    void operator()();
};

class TcpClient
{
    private:
    ContainerPtr received_commands;
    ContainerPtr commands_to_send;
    
    void senderThread(sockpp::stream_socket socket_stream);
    void receiverThread(sockpp::stream_socket socket_stream);

    public:
    TcpClient(ContainerPtr receive_container, ContainerPtr send_container);
    bool startConnection(const std::string& host, const in_port_t& port);
    void sendCommand(const std::string& command);
    bool popCommand(std::string& command);

    friend class std::condition_variable;
};

};

