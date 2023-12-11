#include <iostream>
#include <utility>
#include <string>
#include <bot_lib/Bot.hpp>
#include <commands/QueueContainer.hpp>
#include <connection/TcpClient.hpp>
#include <connection/Client.hpp>

int main(int argc, char* argv[]){
    int port = 12345;

    if(argc > 1)
    {
        port = std::atoi(argv[1]);
    }

    std::cout << "Bot" << std::endl;
    auto clientPtr = std::make_unique<connection::TcpClient>(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());
    clientPtr->startConnection("localhost", port);
    std::string name;
    std::cin >> name;
    bot::Bot bot(name, std::move(clientPtr));
    bot.gameloop();

    return 0;
}