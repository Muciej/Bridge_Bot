#include <memory>
#include <iostream>
#include <vector>
#include <GameEngine/GameManager.hpp>
#include <connection/TcpServer.hpp>
#include <commands/QueueContainer.hpp>

int main(){  

    auto server_ptr = std::make_unique<connection::TcpServer>(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());

    server_ptr->startListening(12345);
    std::cout << "Bridge game server started " << std::endl
              << "waiting for players..." << std::endl;

    game::GameManager manager(std::move(server_ptr));
    manager.gameLoop();

    return 0;
}
