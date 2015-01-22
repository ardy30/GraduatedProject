#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include "Sock_addr.h"

class Tcp_Socket
{
	public:
		Tcp_Socket();
		Tcp_Socket(int fd);
		~Tcp_Socket();

	public:
		int get_sock();
		void set_sock(int fd);

	public:
		int init_sock();
		int close_sock();
		int bind_sock(Sock_addr &sa);
		int listen_sock(int qs);
		int accept_sock(Sock_addr &sa);
		int connect_sock(Sock_addr &sa);
		int read_sock(char *buf, size_t len);
		int read_nr_sock(char *buf, size_t len);
		int write_sock(const char *buf, size_t len);
		int write_nr_sock(const char *buf, size_t len);
		
	public:
		int set_nonblock();
		int set_close_on_exec();
		int set_reuse_addr();
		int set_keep_alive();
		int unset_linger();
		int unset_nagle();

	private:
		int m_fd;
};

#endif

