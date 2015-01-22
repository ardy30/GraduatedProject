#include <iostream>
#include <cstdio>
#include <cstring>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include "Tcp_socket.h"
#include "handle_error.h"

Tcp_Socket::Tcp_Socket(): m_fd(-1)
{}

Tcp_Socket::Tcp_Socket(int fd): m_fd(fd)
{}

Tcp_Socket::~Tcp_Socket()
{
	if(this->m_fd != -1)
		this->close_sock();
}

int Tcp_Socket::get_sock()
{
	return this->m_fd;
}

void Tcp_Socket::set_sock(int fd)
{
	this->m_fd = fd;
}

int Tcp_Socket::init_sock()
{
	this->m_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(this->m_fd < 0)
	{
		handle_syscall_error("Tcp_Socket::init_sock - socket");
		return -1;
	}
	return 0;
}

int Tcp_Socket::close_sock()
{
	if(this->m_fd == -1)
		return 0;
	close(this->m_fd);
	this->m_fd = -1;
	return 0;
}

int Tcp_Socket::bind_sock(Sock_addr &sa)
{
	struct sockaddr_in addr(sa.get_sockaddr_in());
	if(bind(this->m_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		handle_syscall_error("Tcp_Socket::bind_sock bind");
		return -1;
	}
	return 0;
}

int Tcp_Socket::listen_sock(int qs)
{
	if(listen(this->m_fd, qs) < 0)
	{
		handle_syscall_error("Tcp_Socket::listen_sock");
		return -1;
	}
	return 0;
}

int Tcp_Socket::accept_sock(Sock_addr &sa)
{
	int fd(-1);
	struct sockaddr_in addr;	
	unsigned int len(sizeof(addr));
	std::memset(&addr, 0, len);
	if((fd = accept(this->m_fd, (struct sockaddr *)&addr, &len)) < 0)
	{
		handle_syscall_error("Tcp_Socket::accept_sock accept");
		return fd;
	}
	sa.set_by_sockaddr_in(addr, len);
	return fd;
}

int Tcp_Socket::connect_sock(Sock_addr &sa)
{
	struct sockaddr_in addr(sa.get_sockaddr_in());
	return connect(this->m_fd, (struct sockaddr*)&addr, sizeof(addr));
}

int Tcp_Socket::read_sock(char *buf, size_t len)
{
	int count = read(this->m_fd, buf, len);
	return count;
}

int Tcp_Socket::read_nr_sock(char *buf, size_t len)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = buf;
	nleft = len;
	while(nleft > 0)
	{
		if((nread = read(this->m_fd, ptr, nleft)) < 0)
		{
			if(errno == EINTR)
				nread = 0;
			else
            {
                handle_syscall_error("Tcp_Socket::read_nr_sock - read");          
				return -1;
            }
		}
		else if(nread == 0)
			break;
		nleft -= nread;
		ptr += nread;
	}
	return len - nleft;
}

int Tcp_Socket::write_sock(const char *buf,size_t len)
{
	int count = write(this->m_fd, buf, len);
	return count;
}

int Tcp_Socket::write_nr_sock(const char *buf, size_t len)
{
	size_t nleft;
	ssize_t nwriten;
	const char *ptr;
	
	ptr = buf;
	nleft = len;
	while(nleft > 0)
	{
		if((nwriten = write(this->m_fd, ptr, nleft)) <= 0)
		{
			if(nwriten < 0 && errno == EINTR)
				nwriten = 0;
			else
            {
                handle_syscall_error("Tcp_Socket::write_nr_sock - write");
				return -1;
            }
		}
		nleft -= nwriten;
		ptr += nwriten;
	}
	
	return len;
}

int Tcp_Socket::set_nonblock()
{
	int val(-1);
	if((val = fcntl(this->m_fd, F_GETFL, 0)) < 0)
	{
		handle_syscall_error("Tcp_Socket::set_nonblock fcntl");
		return -1;
	}
	val |= O_NONBLOCK;
	if(fcntl(this->m_fd, F_SETFL, val) < 0)
	{
		handle_syscall_error("Tcp_Socket::set_nonblock fcntl");
		return -1;
	}
	return 0;
}

int Tcp_Socket::set_close_on_exec()
{
	int val(-1);
	if((val = fcntl(this->m_fd, F_GETFL, 0)) < 0)
	{
		handle_syscall_error("Tcp_Socket::set_nonblock fcntl");
		return -1;
	}
	val |= FD_CLOEXEC;
	if(fcntl(this->m_fd, F_SETFL, val) < 0)
	{
		handle_syscall_error("Tcp_Socket::set_nonblock fcntl");
		return -1;
	}
	return 0;
}

int Tcp_Socket::set_reuse_addr()
{
	int val(-1);
	if(setsockopt(this->m_fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&val, sizeof(val)) < 0)
	{
		handle_syscall_error("Tcp_Socket::set_reuse_addr");
		return -1;
	}
	return 0;
}

int Tcp_Socket::set_keep_alive()
{
	int val(-1);
	if(setsockopt(this->m_fd, SOL_SOCKET, SO_KEEPALIVE,	 (const void*)&val, sizeof(val)) < 0)
	{
		handle_syscall_error("Tcp_Socket::set_keep_alive");
		return -1;
	}
	return 0;
}

int Tcp_Socket::unset_linger()
{
	struct linger ling = {0, 0};
	if(setsockopt(this->m_fd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling)) < 0)
	{
		handle_syscall_error("Tcp_Socket::unset_linger");
		return -1;
	}
	return 0;
}

int Tcp_Socket::unset_nagle()
{
	int val(-1);
	if(setsockopt(this->m_fd, IPPROTO_TCP, TCP_NODELAY, (const void*)&val, sizeof(val)) < 0)
	{
		handle_syscall_error("Tcp_Socket::unset_nagle");
		return -1;
	}
	return 0;
}

