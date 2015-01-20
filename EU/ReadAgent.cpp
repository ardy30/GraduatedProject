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
    read_len = MSGHEAD_LEN;
    read_complete = true;
}

ReadAgent::~ReadAgent()
{

}

int ReadAgent::read_socket(int fd, unsigned char* ptr, int* len)
{
    int n;

    if((n = read(fd, ptr,*len)) < 0)
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
        *len = *len - n;
        if(*len > 0)
        {
            return READ_BLOCK;
        }
        else if(*len == 0)
            return READ_SUCCESS;
    }
}

