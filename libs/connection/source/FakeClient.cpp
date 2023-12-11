#include <connection/FakeClient.hpp>

namespace connection
{

bool FakeClient::startConnection( const std::string& host,  const in_port_t& port)
{
    return true;
}

void FakeClient::sendCommand(const std::string& command)
{
    sent.push_back(command);
}

bool FakeClient::popCommand(std::string& command)
{
    if(to_receive.empty())
    {
        return false;
    }
    else
    {
        command = to_receive.back();
        to_receive.pop_back();
        return true;
    }
}

std::string FakeClient::popCommandWait()
{
    if(to_receive.empty())
    {
        return "TEST COMMAND";
    }
    else
    {
        auto command = to_receive.back();
        to_receive.pop_back();
        return command;
    }
}



} // namespace connection
