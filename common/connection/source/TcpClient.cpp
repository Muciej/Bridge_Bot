#include <connection/TcpClient.hpp>

void TcpClient::read_thr(sockpp::tcp_socket rdSock)
{
    char buf[512];
    ssize_t n;
    std::stringstream ss;

    while ((n = rdSock.read(buf, sizeof(buf))) > 0 && !shouldStop) {
        // std::scoped_lock lock{inMsgContainer->mutex};
        // inMsgContainer->pushCommand(std::string(buf, n));
    }

    if (n < 0) {
        ss.clear();
        ss << "Read error [" << rdSock.last_error() << "]: " 
            << rdSock.last_error_str();
        throw std::runtime_error(ss.str());
    }
    rdSock.shutdown();
}

void TcpClient::write_thr(sockpp::tcp_socket wrSock)
{
    std::string s;
    while(!shouldStop)
    {
        // std::scoped_lock lock{outMsgContainer->mutex};
        // while(outMsgContainer->popCommand(s))
        // {
        //     if (wrSock.write(s) != (int) s.length()) 
        //     {
        //         if (wrSock.last_error() == EPIPE) 
        //         {
        //             return;
        //         }
        //         else 
        //         {
        //             std::stringstream ss;
        //             ss << "Error writing to the TCP stream ["
        //                << wrSock.last_error()
        //                << "]: "
        //                << wrSock.last_error_str();
        //             throw std::runtime_error(ss.str());
        //         }
        //         break;
        //     }
        // }
    }
}

// TcpClient(MultiThreadCommandContainer* in, MultiThreadCommandContainer* out, const in_port_t& p, const std::string& h = "localhost") 
//     : SocketClient{in, out}, port{std::move(p)}, host{std::move(h)} {};

void TcpClient::startConnection()
{
    sockpp::initialize();
    conn = sockpp::tcp_connector({host, port});
    if (!conn) 
    {
        std::stringstream ss;
        ss << "Error connecting to server at "
            << sockpp::inet_address(host, port)
            << "\n\t" << conn.last_error_str() << std::endl;
            
        throw(std::runtime_error(ss.str()));
    }

    // std::thread rdThr(read_thr, std::move(conn.clone()));
    // std::thread wrThr(write_thr, std::move(conn.clone()));

    // wrThr.detach();
    // rdThr.detach();
}

void TcpClient::write(const std::string& msg)
{
    
}

TcpClient::~TcpClient()
{
    conn.shutdown();
}