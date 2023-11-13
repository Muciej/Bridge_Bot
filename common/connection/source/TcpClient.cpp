#include <connection/TcpClient.hpp>
#include <thread>

namespace connection
{

TcpClient::TcpClient(ContainerPtr receive_container, ContainerPtr send_container) 
    : received_commands(std::move(receive_container)), commands_to_send(std::move(send_container)) {};

bool TcpClient::startConnection(const std::string& host, const in_port_t& port)
{
    sockpp::initialize();

    sockpp::tcp_connector connection({host, port});
    if(!connection)
    {
        std::cerr << "Could not connect to server at"
                  << sockpp::inet_address(host, port)
                  << "\n\t" << connection.last_error_str() << std::endl;
        return false;
    }
    std::cout << "Connected to server on " << connection.address() << std::endl;

    std::thread recThread( [this, &connection] { this->senderThread(connection.clone()); });
    std::thread sendThread( [this, &connection] { this->receiverThread(std::move(connection)); });

    sendThread.detach();
    recThread.join();

    return true;
}

void TcpClient::sendCommand(const std::string& command)
{
    std::scoped_lock{commands_to_send->mutex};
    commands_to_send->pushCommand(command);
}

bool TcpClient::popCommand(std::string& command)
{
    std::scoped_lock{received_commands->mutex};
    return received_commands->popCommand(command);
}

void TcpClient::senderThread(sockpp::stream_socket socket_stream)
{
    std::condition_variable send_condition;
    std::string command;
    while(true)
    {
        std::unique_lock lock{commands_to_send->mutex};
        send_condition.wait(lock, [this] {return !this->commands_to_send->isEmpty(); });
        commands_to_send->popCommand(command);
        lock.unlock();
        if(socket_stream.write(command) != (int) command.length())
        {
            if (socket_stream.last_error() == EPIPE) {
                // todo DELETE DEBUG PRINT
				std::cerr << "It appears that the socket was closed." << std::endl;
			}
			else {
				std::cerr << "Error writing to the TCP stream ["
					<< socket_stream.last_error() << "]: "
					<< socket_stream.last_error_str() << std::endl;
			}
			break;
        }
    }
}

void TcpClient::receiverThread(sockpp::stream_socket socket_stream)
{
    char buf[256];
    ssize_t n;

    while ((n = socket_stream.read(buf, sizeof(buf))) > 0) 
    {
        std::scoped_lock{received_commands->mutex};
        received_commands->pushCommand(std::string(buf, n));
        std::cout << "Command received: " << std::string(buf, n) << std::endl;
	}
}

};
