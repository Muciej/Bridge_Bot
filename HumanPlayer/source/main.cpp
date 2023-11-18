#include <iostream>
#include <connection/TcpClient.hpp>
#include <commands/QueueContainer.hpp>
#include <thread>
#include <chrono>

int main(){

    std::cout << "Human Player" << std::endl;

    connection::TcpClient client(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());

    client.startConnection("localhost", 12345);

    std::string client_name;

    std::cin>>client_name;

    auto is_command = false;
    std::string command;
    while(true)
    {
        is_command = client.popCommand(command);
        if(is_command)
        {
            std::cout << command << std::endl;
            client.sendCommand("Client " + client_name + " received command");
        } else 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    
    return 0;
}