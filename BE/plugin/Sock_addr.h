#ifndef __SOCK_ADDR_H__
#define __SOCK_ADDR_H__

#include <netinet/in.h>
#include <string>

class Sock_addr
{
public:
	Sock_addr();
	~Sock_addr();

public:
	int set(std::string ip, int port = 0);
	int set_by_sockaddr_in(struct sockaddr_in &sin, int socklen);
	std::string get_ip();
	int get_port();
	void get_sockaddr_in(struct sockaddr_in &sin);
	struct sockaddr_in get_sockaddr_in();
	bool operator == (const Sock_addr &sa) const;
	Sock_addr &operator = (const Sock_addr &sa);
	
private:
	std::string m_ip_string;
	int m_port;
	struct sockaddr_in m_sin;
};

#endif

