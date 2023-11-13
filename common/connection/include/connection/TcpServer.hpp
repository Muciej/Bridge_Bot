#pragma once
#include <sockpp/tcp_acceptor.h>
#include <commands/MultiThreadCommandContainer.hpp>
#include <memory>
#include <type_traits>
#include <list>

namespace connection
{

class TcpServer
{
    private:
    in_port_t server_port;
    sockpp::tcp_acceptor acceptor;
    std::unique_ptr<MultiThreadCommandContainer> commands_container;
    std::list<sockpp::tcp_socket> clients_write_sockets;
    
    void clientReader(sockpp::tcp_socket socket);
    void acceptorLoop();

    public:
    TcpServer(std::unique_ptr<MultiThreadCommandContainer> container);
    void startListening(const in_port_t& port);
    void sendToAllClients(const std::string& command);
    bool popCommand(std::string& command);
};

};
