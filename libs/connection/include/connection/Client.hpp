#pragma once
#include <sockpp/tcp_connector.h>
#include <commands/MultiThreadCommandContainer.hpp>

namespace connection
{

class Client
{
    public:

    /// @brief Starts client connection
    /// @param host - server hostname or IP
    /// @param port - port on which client should try to connect
    /// @return true if connection is successful and false otherwise
    virtual bool startConnection(const std::string& host, const in_port_t& port) = 0;

    /// @brief Sends command to server
    /// @param command 
    virtual void sendCommand(const std::string& command) = 0;

    /// @brief Returns command received from server
    /// @param command - obejct in which command should be stores
    /// @return true if some command was received and false otherwise
    virtual bool popCommand(std::string& command) = 0;

    /// @brief Waits until some command is received from server and returns it
    virtual std::string popCommandWait() = 0;
    virtual ~Client() {};
};

} // namespace connection
