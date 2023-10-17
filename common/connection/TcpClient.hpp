#pragma once
#include "SocketClient.hpp"
#include <sockpp/tcp_connector.h>
#include <MultiThreadCommandContainer.hpp>
#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <mutex>

class TcpClient : public SocketClient
{
    private:
    const in_port_t port;
    const std::string host;

    void read_thr(sockpp::tcp_socket rdSock)
    {
        char buf[512];
        ssize_t n;
        std::stringstream ss;

        while ((n = rdSock.read(buf, sizeof(buf))) > 0) {
            std::scoped_lock lock{container->mutex};
            container->pushCommand(std::string(buf, n));
        }

        if (n < 0) {
            ss.clear();
            ss << "Read error [" << rdSock.last_error() << "]: " 
                << rdSock.last_error_str();
            throw std::runtime_error(ss.str());
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

    public:
    TcpClient(MultiThreadCommandContainer* c, const in_port_t& p, const std::string& h = "localhost") 
        : SocketClient(c), port{std::move(p)}, host{std::move(h)} {};

    void startConnection()
    {
        sockpp::initialize();
        sockpp::tcp_connector conn({host, port});
        if (!conn) 
        {
            std::stringstream ss;
            ss << "Error connecting to server at "
                << sockpp::inet_address(host, port)
                << "\n\t" << conn.last_error_str() << std::endl;
                
            throw(std::runtime_error(ss.str()));
	    }

        std::thread rdThr(read_thr, std::move(conn.clone()));
        std::thread wrThr(write_thr, std::move(conn.clone()));

        wrThr.join();
        conn.shutdown(SHUT_WR);
        rdThr.join();
    }


};
