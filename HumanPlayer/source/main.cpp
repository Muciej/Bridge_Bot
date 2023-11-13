#include <iostream>
#include <connection/TcpClient.hpp>
#include <commands/QueueContainer.hpp>

int main(){

    std::cout << "Human Player" << std::endl;

    connection::TcpClient client(std::make_unique<QueueContainer>(), std::make_unique<QueueContainer>());

    client.startConnection("localhost", 12345);
    
    return 0;
}