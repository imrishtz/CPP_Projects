#ifndef SERVER_HPP_	
#define SERVER_HPP_

#include <functional>       // bind
#include <netinet/in.h>     // sockaddr_in

#include "reactor_select.hpp"

using namespace std::placeholders;

namespace ilrd{

typedef Reactor<ReactorSelect> reactor_type;

class Server
{
public:
    Server(int fd_socket, reactor_type& react, int port ,int family = AF_INET, int s_addr = INADDR_ANY);

    void add_client(int fd);
    void handle(int fd);

private:
    int m_fd_socket;
    sockaddr_in m_local;
    reactor_type& m_react;
    static const int LISTEN_BACK_LOG = 10;
    static const int MAX_SIZE = 256;
};

} // end ilrd

#endif //SERVER
