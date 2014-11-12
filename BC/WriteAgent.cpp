/*
 * =====================================================================================
 *
 *       Filename:  WriteAgent.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/20/12 10:43:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include "WriteAgent.h"
WriteAgent::WriteAgent()
{
    //write_len = 0;
}

int WriteAgent::write_socket(int fd, class Buffermanager* buff)
{
    int n;
    if((n = write(fd, buff->bufferptr , buff->buff_length)) < 0)
    {
        if(errno != EWOULDBLOCK) 
        {
            cout << "write sock error:"<< strerror(errno)<< endl;
            return WRITE_ERROR;
        }
        else
            return WRITE_BLOCK;
    }
    else
    {
        buff->front_truncation(n);
        return WRITE_SUCCESS;
    }
}

WriteAgent::~WriteAgent()
{

}
