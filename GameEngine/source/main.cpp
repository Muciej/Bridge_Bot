#include <memory>
#include <iostream>
#include <vector>
#include <GameEngine/GameManager.hpp>
#include <connection/TcpServer.hpp>
#include <commands/QueueContainer.hpp>

int main(int argc, char* argv[]){

    int port = 12345;
    bool print_info = true;

    if(argc > 2)
    {
        std::string yes = "y";
        print_info = yes.compare(argv[2]) ? true : false;
    }
    if(argc > 1)
    {
        port = std::atoi(argv[1]);
    }

    auto server_ptr = std::make_unique<connection::TcpServer>(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());

    server_ptr->startListening(port);
    std::cout << "Bridge game server started " << std::endl
              << "waiting for players..." << std::endl;

    game::GameManager manager(std::move(server_ptr));
    manager.shouldPrintInfo = print_info;
    manager.gameLoop();

    return 0;
}
