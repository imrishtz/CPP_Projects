#include "server.hpp"

namespace ilrd{


Server::Server(int fd_socket, reactor_type& react, int port, int family, int s_addr) :
m_fd_socket(fd_socket), m_react(react)
{
    m_local.sin_family = family;
    m_local.sin_port = htons(port);
    m_local.sin_addr.s_addr = s_addr;

    if (bind(fd_socket, (struct sockaddr *)&m_local, sizeof(sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(fd_socket, LISTEN_BACK_LOG) == -1) {
		perror("listen");
		exit(1);
	}
}
void Server::handle(int fd)
{
    char buff[MAX_SIZE];
    int n = recv(fd, buff, MAX_SIZE, 0);
    if (n <= 0)
    {
        m_react.detach(fd);
        return;
    }
    std::string ret("echo: ");
    buff[n] = '\0';
    ret.append(buff);
    ret.append("\0");
    send(fd, ret.c_str(), ret.size(), 0);
}
void Server::add_client(int fd)
{
    (void)fd;
    sockaddr_in m_remote;
    socklen_t remote_size;
    int new_fd = 0;

    if ((new_fd = accept(m_fd_socket, (struct sockaddr *)&m_remote, &remote_size)) == -1) {
			perror("accept");
    }

    m_react.add(new_fd, std::bind(&Server::handle, *this, new_fd));
}


}// ilrd
