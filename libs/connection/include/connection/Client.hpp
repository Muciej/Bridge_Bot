#pragma once
#include <sockpp/tcp_connector.h>
#include <commands/MultiThreadCommandContainer.hpp>

namespace connection
{

class Client
{
    public:
    virtual bool startConnection(const std::string& host, const in_port_t& port) = 0;
    virtual void sendCommand(const std::string& command) = 0;
    virtual bool popCommand(std::string& command) = 0;
    virtual std::string popCommandWait() = 0;
    virtual ~Client() {};
};

} // namespace connection
