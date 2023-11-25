#pragma once
#include <string>
#include <memory>

#include <sockpp/tcp_acceptor.h>
#include <commands/MultiThreadCommandContainer.hpp>

namespace connection
{

using ContainerPtr = std::unique_ptr<MultiThreadCommandContainer>;

class Server
{
    public:
    virtual void startListening(const in_port_t& port) = 0;
    virtual void sendToAllClients(const std::string& command) = 0;
    virtual bool popCommand(std::string& command) = 0;
    virtual std::string popCommandWait() = 0;
    virtual int getConnectedClientsNumber() = 0;
    virtual ~Server() {};
};

};

