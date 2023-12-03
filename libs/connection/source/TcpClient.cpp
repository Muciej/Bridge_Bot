#include <connection/TcpClient.hpp>
#include <thread>
#include <utility>

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
    std::cout << "Connected to game server on " << connection.address() << std::endl;

    std::thread send_thr(&TcpClient::senderThread, this, std::move(connection.clone()));
    std::thread read_thr(&TcpClient::receiverThread, this, std::move(connection));

    send_thr.detach();
    read_thr.detach();

    return true;
}

void TcpClient::sendCommand(const std::string& command)
{
    std::scoped_lock{commands_to_send->mutex};
    commands_to_send->pushCommand(command);
    send_condition.notify_all();
}

bool TcpClient::popCommand(std::string& command)
{
    std::scoped_lock{received_commands->mutex};
    return received_commands->popCommand(command);
}

std::string TcpClient::popCommandWait()
{
    std::unique_lock lock{received_commands->mutex};
    receive_condition.wait(lock, [this] { return !this->received_commands->isEmpty(); });
    std::string msg;
    received_commands->popCommand(msg);
    return msg;
}

void TcpClient::senderThread(sockpp::tcp_socket socket)
{
    std::string command;
    while(true)
    {
        std::unique_lock lock{commands_to_send->mutex};
        send_condition.wait(lock, [this] {return !this->commands_to_send->isEmpty(); });
        commands_to_send->popCommand(command);
        lock.unlock();
        if(socket.write(command) != (int) command.length())
        {
            if (socket.last_error() == EPIPE) {
				std::cerr << "It appears that the socket was closed." << std::endl;
			}
			else {
				std::cerr << "Error writing to the TCP stream ["
					<< socket.last_error() << "]: "
					<< socket.last_error_str() << std::endl;
			}
			break;
        }
    }
    socket.shutdown(SHUT_WR);
}

void TcpClient::receiverThread(sockpp::tcp_socket socket)
{
    char buf[256];
    ssize_t n;

    while ((n = socket.read(buf, sizeof(buf))) > 0)
    {
        std::scoped_lock{received_commands->mutex};
        received_commands->pushCommand(std::string(buf, n));
        receive_condition.notify_all();
	}
}

};
