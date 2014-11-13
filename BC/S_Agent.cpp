/*
 * =====================================================================================
 *
 *       Filename:  S_Agent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/09/12 10:06:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * ===============================================================================
 */
#include "S_Agent.h"

S_Agent::S_Agent(Epoll *epoll)
{
//    s_manager_agent.s_agent = this;
      //this -> BC = BC;
      this -> m_epoll = epoll;
      error = 0;
      finish = 0;
}

S_Agent::~S_Agent()
{
    if(m_epoll->epoll_delete(this) < 0)
    {
        cout << "epoll_delete error"<<endl;
    }
    close(fd);
}

int S_Agent::getfd()
{
    return fd;
}

int S_Agent::setnonblocking(int fd)
{
    int flag;
    if((flag = fcntl(fd, F_GETFL,0)) < 0)
    {
        cerr <<"fcntl error:"<<endl;
        return -1;
    }
    if(fcntl(fd,F_SETFL,flag|O_NONBLOCK) < 0)
    {
        cerr<<"fcntl error"<<endl;
        return -1;
    }
    return 0;
}

int S_Agent::connect_server(char* IPaddr,int port)
{
    struct sockaddr_in servaddr;
    int sockfd;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if(inet_pton(AF_INET,IPaddr,&servaddr.sin_addr) <= 0)
    {
        cout << "inet_pton error"<<endl;
        delete this;
        return -1;
    }
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        cout << "socket error"<<endl;
        delete this;
        return -1;
    }
    this ->fd = sockfd;
    if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr)) < 0)
    {
        cout << "connect error";
        delete this;
        return -1;
    }
    if(setnonblocking(sockfd) < 0)
    {
        cout << "setnonblocking error"<<endl;
        return -1;
    }
    if(m_epoll->epoll_registe(EPOLLIN,this) < 0)
    {
        cout <<"epoll_registe error"<<endl;
        return -1;
    }

}

int S_Agent::readagent()
{
    int ret;
    ret = S_read.read_socket(fd,&Readbuff);
    if(ret == READ_ERROR)
    {
        cout <<"read_socket error"<<endl;
        error = 1;
        return -1;
    }
    else if(ret == READ_END)
    {
        cout << "TCP disconnect"<< endl;
        error = 1;
        return -1;
    }
    else if(ret == READ_BLOCK)
    {
        cout << "READ_BLOCK"<< endl;
        return 0;
    }
    else if(ret == READ_SUCCESS)
    {
     /*     if(exec() < 0)
        {
            cout << "exec error"<<endl;
            return -1;
        }*/
        if(Writebuff.buff_length != 0)
        {
            if(m_epoll->epoll_modify(EPOLLOUT,this) < 0)
            {
                cout << "epoll_modify error"<<endl;
                delete this;
                return -1;
            }
        }
        return 0;
    }
    

}
/*  int exec()
{
    memcpy(&message_head,s_agent->Readbuff.bufferptr,MESG_HEAD_LEN);
    if(message_head.length == 0)
    {
        finish = 1;
        return 0;
    }
    else
    {
        Readbuff.front_truncation(MESG_HEAD_LEN);
        string temp(Readbuff.bufferptr,mesg_head.length);
        load = temp;
        finish = 1;
        return 0;
    }
}
    */
int S_Agent::writeagent()
{
    int ret;
    ret = S_write.write_socket(fd,&Writebuff);
    if(ret == WRITE_ERROR)
    {
        cout << "write_socket error"<< endl;
        delete this;
        return -1;
    }
    else if(ret == WRITE_BLOCK)
    {
        if(m_epoll->epoll_modify(EPOLLIN,this) < 0)
        {
            cout << "epoll_modify error"<<endl;
            return -1;
        }
        else
            return 0;
    }
    else if(ret == WRITE_SUCCESS)
    {
        if(m_epoll->epoll_modify(EPOLLIN,this) < 0)
        {
            cout << "epoll_modify error"<<endl;
            return -1;
        }
        else
            return 0;
    }
}
