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
    /// @brief Starts server on given port
    virtual void startListening(const in_port_t& port) = 0;

    /// @brief Sends command to all clients
    /// @param command - command to send
    virtual void sendToAllClients(const std::string& command) = 0;

    /// @brief Pops command that server received
    /// @param command - obejct in which command should be saved
    /// @return true if there was some command received and false otherwise
    virtual bool popCommand(std::string& command) = 0;

    /// @brief Waits until there is some command received and then returns it
    virtual std::string popCommandWait() = 0;

    /// @brief Returns number of connected clients
    virtual int getConnectedClientsNumber() = 0;
    virtual ~Server() {};
};

};

