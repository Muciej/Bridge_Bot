#include <iostream>
#include <GameEngine/GameManager.hpp>
#include <connection/TcpServer.hpp>
#include <commands/QueueContainer.hpp>
#include <GameEngine/Player.hpp>
#include <vector>

int main(){  

    connection::TcpServer server(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());

    server.startListening(12345);
    std::cout << "Bridge game server started " << std::endl
              << "waiting for players..." << std::endl;

    Game::GameManager manager;
    manager.gameLoop(server);

    return 0;
}
