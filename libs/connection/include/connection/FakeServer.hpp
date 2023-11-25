#pragma once
#include <string>
#include <connection/Server.hpp>
#include <sockpp/tcp_acceptor.h>

namespace test
{

    class FakeServer : public connection::Server
    {
        public:
        in_port_t set_port;
        std::string last_command_to_send;
        void startListening(const in_port_t& port) override;
        void sendToAllClients(const std::string& command) override;
        bool popCommand(std::string& command) override;
        std::string popCommandWait() override;
        int getConnectedClientsNumber() override;
    };

};
