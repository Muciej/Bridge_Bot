#pragma once
#include <sockpp/tcp_acceptor.h>
#include <commands/MultiThreadCommandContainer.hpp>
#include <memory>
#include <type_traits>
#include <list>
#include <condition_variable>

namespace connection
{

using ContainerPtr = std::unique_ptr<MultiThreadCommandContainer>;

class TcpServer
{
    private:
    in_port_t server_port;
    sockpp::tcp_acceptor acceptor;

    ContainerPtr received_commands;
    ContainerPtr commands_to_send;

    std::condition_variable send_condition;
    std::list<sockpp::tcp_socket> clients_write_sockets;
    
    void acceptorLoop();
    void clientReader(sockpp::tcp_socket socket);
    void allClientSender();

    public:
    TcpServer(ContainerPtr receive_container, ContainerPtr send_container);
    void startListening(const in_port_t& port);
    void sendToAllClients(const std::string& command);
    bool popCommand(std::string& command);
    int getConnectedClientsNumber();
};

};
