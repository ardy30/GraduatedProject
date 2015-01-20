/*
 * =====================================================================================
 *
 *       Filename:  Listenagent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年09月19日 13时56分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#include "head.h"
#include "Agent.h"
#include "Epoll.h"
#include "I_Listenagent.h"
#include "I_Manager_Agent.h"
#include "I_Agent.h"
I_Listenagent::I_Listenagent()
{
    m_port = 32600;
    fd = -1;
}
int I_Listenagent::setnonblocking (int fd) const
{
    int flag;
    if((flag = fcntl(fd, F_GETFL, 0)) < 0)
    {
        cerr<<"fcntl error:"<<"\n"<<endl;
        return -1;
    }
    if(fcntl(fd,F_SETFL,flag|O_NONBLOCK) < 0)
    {
        cerr<<"fcntl error:"<<"\n"<<endl;
        return -1;
    }
    return 0;
}

int I_Listenagent::initialserver()
{
    struct sockaddr_in servaddr;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(m_port);
    if((fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        cerr<<"socket error:"<<strerror(errno)<<"\n"<<endl;
        return -1;
    }
    if(bind(fd,(struct sockaddr *)&servaddr, sizeof(servaddr)) <0)
    {
        cerr<<"bind error:"<<strerror(errno)<<"\n"<<endl;
        return -1;
    }
    if(m_epoll.epoll_registe(EPOLLIN,this) < 0)
    {
        cout<<"m_epoll->epoll_registe error\n"<<endl;    
    }
    if(listen(fd,LISTENQ) < 0)
    {
        cerr<<"listen error:"<<strerror(errno)<<"\n"<<endl;
        return -1;
    }
    return 0;
}

int I_Listenagent::readagent()
{
    int connfd;
    int flag;
    int ret;
    socklen_t clilen;
    sockaddr_in cliaddr;
    clilen = sizeof(cliaddr);
    if((connfd = accept(fd, (SA *)&cliaddr,&clilen)) < 0)
    {
        cerr<<"accept error"<<strerror(errno)<<endl;
        return -1;
    }
    if(setnonblocking(connfd) < 0)
    {
        cout<<"setnonblocking error"<<endl;
        return -1;
    }
    flag = 1;
    ret = setsockopt(connfd ,IPPROTO_TCP,TCP_NODELAY,(const char*)&flag,sizeof(flag));
    if(ret == -1)
    {
        cout << "couldn't setsockopt(TCP_NODELAY)"<<strerror(errno)<<endl;
    }
    Agent* agent = new I_Agent(connfd);    
    if(m_epoll.epoll_registe(EPOLLIN,agent) < 0)
    {
        cout<<"m_epoll->epoll_registe error\n"<<endl;
        return -1;
    }
    return 0;
}
