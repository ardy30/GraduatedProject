/*
 * =====================================================================================
 *
 *       Filename:  D_Agent.cpp
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
#include "D_Agent.h"

D_Agent::D_Agent(int D_fd)
{
    this -> fd = D_fd;
    read_len = MESG_HEAD_LEN;
    Readbuff_head.new_buff(MESG_HEAD_LEN);
    read_stat = READ_MESGHEAD;
    Readbuff = &Readbuff_head;
    if(d_manager_agent.add_d_agent(this) < 0)
    {
        cout <<"add_d_agent error"<<endl;
        close(fd);
        delete this;
    }
}

D_Agent::~D_Agent()
{
    if(m_epoll.epoll_delete(this) < 0)
    {
        cout << "epoll_delete error"<<endl;
    }
    close(fd);
}

int D_Agent::getfd()
{
    return fd;
}



int D_Agent::readagent()
{
    int ret;
    for(;;)
    {
        ret = D_read.read_socket(fd,Readbuff -> bufferptr + Readbuff -> buff_length - read_len,&read_len);
        if(ret == READ_ERROR)
        {
            cout <<"read_socket error"<<endl;
            delete this;
            return -1;
        }
        else if(ret == READ_END)
        {
            cout << "TCP disconnect"<< endl;
            delete this;
            return 0;
        }
        else if(ret == READ_BLOCK)
        {
            if(Writebuff.head != NULL)
            {
                if(m_epoll.epoll_modify(EPOLLOUT,this) < 0)
                {
                    cout << "epoll_modify error"<<endl;
                    delete this;
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

}
    
int D_Agent::writeagent()
{
    int ret;
    ret = D_write.write_socket(fd,&Writebuff);
    if(ret == WRITE_ERROR)
    {
        cout << "write_socket error"<< endl;
        delete this;
        return -1;
    }
    else if(ret == WRITE_BLOCK)
    {
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

int D_Agent::package_head_data()
{
   if(read_stat == READ_MESGHEAD)
   {
      memcpy(&i_o_head, Readbuff_head.bufferptr,MESG_HEAD_LEN) ;
      if(i_o_head.opcode == RESPONSE_READ)
      {
            Readbuff_data.delete_buff();
            Readbuff_data.new_buff(i_o_head.len*BLOCK_SIZE);
            read_len = i_o_head.len*BLOCK_SIZE;
            read_stat = READ_DATA;
            Readbuff = &Readbuff_data;
            return 0;
      }
   }
   if(d_manager_agent.exec(this) < 0)
   {
        cout << "d_manager_agent error"<< endl;
        return -1;
   }
   else
   {
        read_len = MESG_HEAD_LEN;
        read_stat = READ_MESGHEAD;
        Readbuff = &Readbuff_head;
        return 0;
   
   }

}


