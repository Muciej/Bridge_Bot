#include <connection/TcpServer.hpp>
#include <utility>
#include <iostream>
#include <thread>
#include <functional>
#include <mutex>

namespace connection
{


TcpServer::TcpServer(std::unique_ptr<MultiThreadCommandContainer> container) : commands_container(std::move(container)) {}

void TcpServer::startListening(const in_port_t& port)
{
    sockpp::initialize();
    acceptor = sockpp::tcp_acceptor(port);

    if (!acceptor) 
    {
		std::cerr << "Error creating the acceptor: " << acceptor.last_error_str() << std::endl;
	}
	std::cout << "Started server on port " << port << "..." << std::endl;
    std::thread thr( [this] {this->acceptorLoop();});
    thr.detach();
}

void TcpServer::acceptorLoop()
{
    while (true)
    {
        sockpp::inet_address peer;

        sockpp::tcp_socket socket = acceptor.accept(&peer);
        std::cout << "Received a connection request from " << peer << std::endl;

        if (socket)
        {
            // std::thread rd_thr( [this, &socket] { this->clientReader(socket.clone()); } );
            clients_write_sockets.push_back(std::move(socket));
            // rd_thr.detach();
        } else
        {
            std::cerr << "Error accepting incoming connection: "
                << acceptor.last_error_str() << std::endl;            
        }
    }
}

void TcpServer::clientReader(sockpp::tcp_socket socket)
{
    char buf[512];
    ssize_t n;

    while ((n = socket.read(buf, sizeof(buf))) > 0) 
    {
        std::scoped_lock{commands_container->mutex};
        commands_container->pushCommand(std::string(buf, n));
	}

	if (n < 0) 
    {
		std::cout << "Read error [" << socket.last_error() << "]: " 
			<< socket.last_error_str() << std::endl;
	}
	socket.shutdown();    
}

void TcpServer::sendToAllClients(const std::string &command)
{
    for(auto it = clients_write_sockets.begin(); it != clients_write_sockets.end(); it++)
    {
        // todo DELETE DEBUG PRINT
        std::cout <<"Entering here?" << std::endl;
        if(it->write(command) != (int) command.length())
        {
            clients_write_sockets.erase(it);
            std::cerr << "Client connection closed" << std::endl;
            if(it == clients_write_sockets.end())
            {
                return;
            }
        }
    }
}

bool TcpServer::popCommand(std::string& command)
{
    std::scoped_lock{commands_container->mutex};
    return commands_container->popCommand(command);
}

};
