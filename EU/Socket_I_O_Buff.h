/*
 * =====================================================================================
 *
 *       Filename:  Socket_I_O_Buff.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/23/12 16:38:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _Socket_I_O_Buff_H
#define _Socket_I_O_Buff_H

#include "head.h"
class Socket_I_O_Buff
{
    public:
        Socket_I_O_Buff();
        ~Socket_I_O_Buff();
        struct data_list* head;
        struct data_list* rear;
        int new_buff(int);
        int delete_buff();
        int add_buff(void* ,int);
};

#endif
