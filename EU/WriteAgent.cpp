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
    write_len = 0;
}

int WriteAgent::write_socket(int fd, class Socket_I_O_Buff* buff)
{
    int n;
    for(;;)
    {
        if(buff -> head == NULL)
        {
            write_len = 0;
            return WRITE_SUCCESS;
        }

        if(write_len == 0)
        {
            write_len = buff-> head->len;

        }
        if((n = write(fd, buff->head->ptr + buff-> head->len - write_len , write_len)) < 0)
        {
            if(errno != EWOULDBLOCK) 
            {
                cout << "write sock error:"<< strerror(errno)<< endl;
                return WRITE_ERROR;
            }
            else
                return WRITE_BLOCK;
        }
        else if(n < write_len)
        {
            write_len = write_len - n;
            return WRITE_BLOCK;
        }
        else
        {
            write_len = write_len - n;
            struct data_list* temp;
            temp = buff->head;
            buff-> head = buff-> head->next_data_block;
            delete temp -> ptr;
            delete temp;
            if(buff -> head == NULL)
                buff -> rear =NULL;
        }
    }
}

WriteAgent::~WriteAgent()
{

}
