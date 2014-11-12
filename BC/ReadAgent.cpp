/*
 * =====================================================================================
 *
 *       Filename:  ReadAgent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/17/12 11:45:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "ReadAgent.h"

ReadAgent::ReadAgent()
{
    read_len = TCP_SOCKET_SIZE;
    read_complete = true;
}

ReadAgent::~ReadAgent()
{

}

int ReadAgent::read_socket(int fd, class Buffermanager* buff)
{
    int n;
    class Buffermanager temp;
    if((temp.new_buff(TCP_SOCKET_SIZE)) < 0)
    {
        cout << "new_buff error"<< endl;
        return -1;
    }
    if((n = read(fd, temp.bufferptr, TCP_SOCKET_SIZE)) < 0)
    {
        if(errno != EWOULDBLOCK)
        {
            cout<< "read error:" <<strerror(errno)<<endl;
            return READ_ERROR;
        }
        else
            return READ_BLOCK;
    }
    else if(n == 0)
    {
        cout << "FIN"<< endl;
        return READ_END;
    }
    else
    {
        buff->add_buff(temp.bufferptr,n);
        temp.delete_buff();
        return READ_SUCCESS;
    }
}

