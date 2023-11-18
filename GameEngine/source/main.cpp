#include <iostream>
#include <thread>
#include <chrono>
#include <GameEngine/GameManager.hpp>
#include <connection/TcpServer.hpp>
#include <commands/QueueContainer.hpp>

int main(){  

    connection::TcpServer server(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());

    server.startListening(12345);

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        server.sendToAllClients("test");
        std::cout << "send, no of clients: " << server.getConnectedClientsNumber() << std::endl;
    }

    return 0;
}