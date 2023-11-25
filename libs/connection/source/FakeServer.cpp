#include <connection/FakeServer.hpp>

namespace test
{

void FakeServer::startListening(const in_port_t& port)
{
    set_port = port;
}

void FakeServer::sendToAllClients(const std::string& command)
{
    last_command_to_send = command;
}

bool FakeServer::popCommand(std::string& command)
{
    command = "Test command";
    return true;
}

std::string FakeServer::popCommandWait()
{
    return "Test command";
}

int FakeServer::getConnectedClientsNumber()
{
    return 4;
}


};

