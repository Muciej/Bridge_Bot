#include <connection/TcpClient.hpp>
#include <commands/QueueContainer.hpp>
#include <memory>
#include <iostream>
#include <string>

int main()
{
    connection::TcpClient client{std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>()};

    client.startConnection("localhost", 12345);
    std::string command;
    while(true)
    {
        std::cin >> command;
        client.sendCommand(command);
    }

    return 0;
}