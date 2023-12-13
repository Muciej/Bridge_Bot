#pragma once
#include <memory>
#include <type_traits>
#include <list>
#include <condition_variable>

#include <sockpp/tcp_acceptor.h>
#include <connection/Server.hpp>

namespace connection
{


/// @brief TCP implementation of Server interface
class TcpServer : public Server
{
    private:
    in_port_t server_port;
    sockpp::tcp_acceptor acceptor;

    ContainerPtr received_commands;
    ContainerPtr commands_to_send;

    std::condition_variable send_condition;
    std::condition_variable receive_condition;
    std::list<sockpp::tcp_socket> clients_write_sockets;
    
    void acceptorLoop();
    void clientReader(sockpp::tcp_socket socket);
    void allClientSender();

    public:
    TcpServer(ContainerPtr receive_container, ContainerPtr send_container);
    void startListening(const in_port_t& port) override;
    void sendToAllClients(const std::string& command) override;
    bool popCommand(std::string& command) override;
    std::string popCommandWait() override;
    int getConnectedClientsNumber() override;
};

};
