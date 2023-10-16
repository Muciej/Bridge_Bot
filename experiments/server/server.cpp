#include <iostream>
#include <thread>
#include <queue>
#include <sockpp/tcp_acceptor.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void run_echo(sockpp::tcp_socket socket)
{
    ssize_t n;
	char buf[512];

	while ((n = socket.read(buf, sizeof(buf))) > 0)
    {
        socket.write("Message received");
        cout.write(buf, n);
        cout << endl;
    }
	cout << "Connection closed from " << socket.peer_address() << endl;
}

int main()
{
    std::cout << "Basic server test" << std::endl;

    sockpp::initialize();

    const in_port_t port = 12345;

    sockpp::tcp_acceptor acc(port);

    if (!acc) 
    {
		cerr << "Error creating the acceptor: " << acc.last_error_str() << endl;
		return 1;
	}
	cout << "Awaiting connections on port " << port << "..." << endl;

    while (true)
    {
        sockpp::inet_address peer;

        sockpp::tcp_socket socket = acc.accept(&peer);
        cout << "Received a connection request from " << peer << endl;

        if (!socket)
        {
            cerr << "Error accepting incoming connection: "
                << acc.last_error_str() << endl;
        } else
        {
            std::thread thr(run_echo, std::move(socket));
            thr.detach();
        }
    }

    return 0;
}
