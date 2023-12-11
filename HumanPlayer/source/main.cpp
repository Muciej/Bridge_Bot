#include <iostream>
#include <connection/TcpClient.hpp>
#include <commands/QueueContainer.hpp>
#include <HumanPlayer/HumanPlayer.hpp>

int main(int argc, char* argv[]){

    int port = 12345;

    if(argc > 1)
    {
        port = std::atoi(argv[1]);
    }

    std::cout << "Human Player" << std::endl;
    auto clientPtr = std::make_unique<connection::TcpClient>(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());
    clientPtr->startConnection("localhost", port);
    HumanPlayer humanPlayer(std::move(clientPtr));
    humanPlayer.gameloop();
    return 0;
}
