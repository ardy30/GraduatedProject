#ifndef _PLUGIN_INTERFACE_H
#define _PLUGIN_INTERFACE_H
#include <string>
#include "Tcp_socket.h"
#include "Sock_addr.h"

class Plugin_interface
{
	public:
		void start();
		void notify();
		void stop();

	private:
		Tcp_Socket m_sock;
};

#endif

