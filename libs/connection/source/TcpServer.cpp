#include <connection/TcpServer.hpp>
#include <utility>
#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace connection
{

TcpServer::TcpServer(ContainerPtr receive_container, ContainerPtr send_container)
    : received_commands(std::move(receive_container)), commands_to_send(std::move(send_container)) {};

void TcpServer::startListening(const in_port_t& port)
{
    sockpp::initialize();
    acceptor = sockpp::tcp_acceptor(port);

    if (!acceptor)
    {
		std::cerr << "Error creating the acceptor: " << acceptor.last_error_str() << std::endl;
	}
	std::cout << "Started server on port " << port << "..." << std::endl;
    std::thread acceptor_thr( [this] {this->acceptorLoop();});
    std::thread all_sender_thr( [this] {this->allClientSender();});
    acceptor_thr.detach();
    all_sender_thr.detach();
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
            clients_write_sockets.push_back(std::move(socket.clone()));
            std::thread read_thr(&TcpServer::clientReader, this, std::move(socket));
            read_thr.detach();
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
        std::cout << "Received: " << std::string(buf, n) << std::endl;
        std::scoped_lock{received_commands->mutex};
        received_commands->pushCommand(std::string(buf, n));
        receive_condition.notify_all();
	}

	if (n < 0)
    {
		std::cout << "Read error [" << socket.last_error() << "]: "
			<< socket.last_error_str() << std::endl;
	}
	socket.shutdown(SHUT_RDWR);
}

void TcpServer::allClientSender()
{
    std::string command;
    while(true)
    {
        std::unique_lock lock{commands_to_send->mutex};
        send_condition.wait(lock, [this] { return !this->commands_to_send->isEmpty(); });
        commands_to_send->popCommand(command);
        lock.unlock();
        for(auto it = clients_write_sockets.begin(); it != clients_write_sockets.end(); it++)
        {
            if(it->write(command) != (int) command.length())
            {
                it->close();
                it = clients_write_sockets.erase(it);
                std::cerr << "Client connection closed" << std::endl;
            }
        }
    }
}

void TcpServer::sendToAllClients(const std::string &command)
{
    std::cout << "TCPSERVER: sending: " << command;
    std::scoped_lock{commands_to_send->mutex};
    commands_to_send->pushCommand(command);
    send_condition.notify_all();
}

bool TcpServer::popCommand(std::string& command)
{
    std::scoped_lock{received_commands->mutex};
    return received_commands->popCommand(command);
}

std::string TcpServer::popCommandWait()
{
    std::unique_lock lock{received_commands->mutex};
    receive_condition.wait(lock, [this] { return !this->received_commands->isEmpty(); });
    std::string msg;
    received_commands->popCommand(msg);
    return msg;
}

int TcpServer::getConnectedClientsNumber()
{
    return clients_write_sockets.size();
}
};
