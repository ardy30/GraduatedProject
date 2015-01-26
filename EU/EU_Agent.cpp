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
#include "EU_Agent.h"

EU_Agent::EU_Agent()
{
    read_len = MSGHEAD_LEN;
    Readbuff_head.new_buff(MSGHEAD_LEN);
    Readbuff = &Readbuff_head;
    read_stat = READ_MESGHEAD;
    error = 0;
}

EU_Agent::EU_Agent(int I_fd)
{
    this -> fd = I_fd;
    read_len = MSGHEAD_LEN;
    Readbuff_head.new_buff(MSGHEAD_LEN);
    Readbuff = & Readbuff_head;
    read_stat = READ_MESGHEAD;
    error = 0;
}

EU_Agent::~EU_Agent()
{
    if(m_epoll.epoll_delete(this) < 0)
    {
        cout << "epoll_delete error"<<endl;
    }
    close(fd);
}

int EU_Agent::getfd()
{
    return fd;
}

int EU_Agent::setnonblocking(int fd)
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

int EU_Agent::connect_server(char* IPaddr)
{
    struct sockaddr_in servaddr;
    int sockfd;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(EU_EU_PORT);
    if(inet_pton(AF_INET,IPaddr,&servaddr.sin_addr) <= 0)
    {
        cout << "inet_pton error"<<endl;
        error = 1;
        //delete this;
        return -1;
    }
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        cout << "socket error"<<endl;
        error =1;
        //delete this;
        return -1;
    }
    this ->fd = sockfd;
    if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr)) < 0)
    {
        cout << "connect error";
        //delete this;
        error = 1;
        return -1;
    }
    if(setnonblocking(sockfd) < 0)
    {
        cout << "setnonblocking error"<<endl;
        error = 1;
        return -1;
    }
    if(m_epoll.epoll_registe(EPOLLOUT,this) < 0)
    {
        cout <<"epoll_registe error"<<endl;
        error = 1;
        return -1;
    }

}

int EU_Agent::readagent()
{
    int ret;
    ret = EU_read.read_socket(fd,Readbuff->bufferptr + Readbuff -> buff_length -read_len,&read_len);
    if(ret == READ_ERROR)
    {
        cout <<"read_socket error"<<endl;
        error =1;
        //delete this;
        return -1;
    }
    else if(ret == READ_END)
    {
        cout << "TCP disconnect"<< endl;
        error = 1;
        //delete this;
        return 0;
    }
    else if(ret == READ_BLOCK)
    {
        if(Writebuff.head!=NULL)
        {
            if(m_epoll.epoll_modify(EPOLLOUT,this) < 0)
            {
                cout << "epoll_modify error"<< endl;
                //delete this;
                error =1 ;
                return -1;
            }
        }
        return 0;
    }
    else if(ret == READ_SUCCESS)
    {
        if(package_head_data() < 0)
        {
            cout << "package_head_data error"<<endl;
            return -1;
        }
    }
    

}
    
int EU_Agent::writeagent()
{
    int ret;
    ret = EU_write.write_socket(fd,&Writebuff);
    if(ret == WRITE_ERROR)
    {
        cout << "write_socket error"<< endl;
        error = 1;
        //delete this;
        return -1;
    }
    else if(ret == WRITE_BLOCK)
    {
      /*   if(m_epoll.epoll_modify(EPOLLIN,this) < 0)
        {
            cout << "epoll_modify error"<<endl;
            return -1;
        }
        else*/
            return 0;
    }
    else if(ret == WRITE_SUCCESS)
    {
        if(m_epoll.epoll_modify(EPOLLIN,this) < 0)
        {
            cout << "epoll_modify error"<<endl;
            return -1;
        }
        else
            return 0;
    }
}

int EU_Agent::package_head_data()
{
    if(read_stat == READ_MESGHEAD)
    {
        Head = (struct mesg_head*)(Readbuff_head.bufferptr);
        Readbuff_data.delete_buff();
        if(Head -> length > 0)
        {
            Readbuff_data.new_buff(Head -> length);
            read_len = Head -> length;

            Readbuff = &Readbuff_data;
            read_stat = READ_DATA;
            return 0;
        }
    }
    if(exec()< 0)
    {
        cout << "EUAgent exec error"<< endl;
        return -1;
    }
    else
    {
        read_len = MSGHEAD_LEN;
        read_stat = READ_MESGHEAD;
        Readbuff = &Readbuff_head;
        return 0;
    }
}

int EU_Agent::exec()
{
    if(0 > cmnd_exec())
    {
        cout << "EU_Agent cmnd_exec error"<< endl;
        return -1;
    }
    return 0;
}

int EU_Agent::cmnd_exec()
{
    if(Head -> cmd == MSG_EU_EU_SHUFFLE)
    {
        return 0;
    }
    if(Head -> cmd == MSG_EU_EU_SHUFFLE_ACK)
    {
        return 0;
    }
        
}
