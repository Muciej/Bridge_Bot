#include <connection/TcpServer.hpp>
#include <commands/QueueContainer.hpp>
#include <memory>
#include <iostream>

int main()
{
    connection::TcpServer server{std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>()};

    server.startListening(12345);

    while(true)
    {
        std::cout << server.popCommandWait() << std::endl;
    }

    return 0;
}