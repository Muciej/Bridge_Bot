#include <iostream>
#include <connection/TcpClient.hpp>
#include <commands/QueueContainer.hpp>
#include <HumanPlayer/HumanPlayer.hpp>

int main(){

    std::cout << "Human Player" << std::endl;
    auto clientPtr = std::make_unique<connection::TcpClient>(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());
    clientPtr->startConnection("localhost", 12345);
    HumanPlayer humanPlayer(std::move(clientPtr));
    humanPlayer.gameloop();
    return 0;
}
