#include <iostream>
#include <utility>
#include <string>
#include <bot/Bot.hpp>
#include <commands/QueueContainer.hpp>
#include <connection/TcpClient.hpp>

int main(){

    std::cout << "Bot" << std::endl;
    auto clientPtr = std::make_unique<connection::TcpClient>(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());
    clientPtr->startConnection("localhost", 12345);
    std::string name;
    std::cin >> name;
    bot::Bot bot(std::move(clientPtr), name);
    bot.gameloop();

    return 0;
}