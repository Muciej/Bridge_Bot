#pragma once
#include <sockpp/tcp_connector.h>
#include <memory>
#include <condition_variable>
#include <commands/MultiThreadCommandContainer.hpp>
#include <connection/Client.hpp>

namespace connection
{

using ContainerPtr = std::unique_ptr<MultiThreadCommandContainer>;

class TcpClient : public Client
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
    bool startConnection(const std::string& host, const in_port_t& port) override;
    void sendCommand(const std::string& command) override;
    bool popCommand(std::string& command) override;
    std::string popCommandWait() override;

};

};

