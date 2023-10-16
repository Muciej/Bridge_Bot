#include <iostream>
#include <thread>
#include <string>
#include <sockpp/tcp_connector.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void read_thr(sockpp::tcp_socket rdSock)
{
	char buf[512];
	ssize_t n;

	while ((n = rdSock.read(buf, sizeof(buf))) > 0) {
		cout.write(buf, n);
		cout << endl;
	}

	if (n < 0) {
		cout << "Read error [" << rdSock.last_error() << "]: " 
			<< rdSock.last_error_str() << endl;
	}
	rdSock.shutdown();
}

void write_thr(sockpp::tcp_socket wrSock)
{
    std::string s, sret;
	while (getline(cin, s) && !s.empty()) {
		if (wrSock.write(s) != (int) s.length()) {
			if (wrSock.last_error() == EPIPE) {
				cerr << "It appears that the socket was closed." << endl;
			}
			else {
				cerr << "Error writing to the TCP stream ["
					<< wrSock.last_error() << "]: "
					<< wrSock.last_error_str() << endl;
			}
			break;
		}
	}
}

// --------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	const std::string host = "localhost";
	const in_port_t port = (argc > 1) ? atoi(argv[1]) : 12345;

	sockpp::initialize();

	// Implicitly creates an inet_address from {host,port}
	// and then tries the connection.

	sockpp::tcp_connector conn({host, port});
	if (!conn) {
		cerr << "Error connecting to server at "
			<< sockpp::inet_address(host, port)
			<< "\n\t" << conn.last_error_str() << endl;
		return 1;
	}

	cout << "Created a connection from " << conn.address() << endl;

	// We create a read thread and send it a clone (dup) of the
	// connector socket. 

	std::thread rdThr(read_thr, std::move(conn.clone()));
    std::thread wrThr(write_thr, std::move(conn.clone()));

	int ret = !conn ? 1 : 0;

	// Shutting down the socket will cause the read thread to exit.
	// We wait for it to exit before we leave the app.
    wrThr.join();
	conn.shutdown(SHUT_WR);
	rdThr.join();

	return ret;
}
