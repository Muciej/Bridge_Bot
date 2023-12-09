#pragma once
#include <vector>
#include <string>
#include <sockpp/tcp_connector.h>
#include <connection/Client.hpp>

namespace connection
{

class FakeClient : public Client
{
    private:
    std::vector<std::string> sent;
    std::vector<std::string> to_receive;

    public:
    FakeClient() = default;
    FakeClient(std::vector<std::string>& _to_receive) : to_receive(std::move(_to_receive)) {};
    bool startConnection(const std::string& host, const in_port_t& port);
    void sendCommand(const std::string& command);
    bool popCommand(std::string& command);
    std::string popCommandWait();

};

};
