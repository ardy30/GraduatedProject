/*
 * =====================================================================================
 *
 *       Filename:  D_Agent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/09/12 10:06:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _D_AGENT_H_
#define _D_AGENT_H_
#include "head.h"
#include "D_Manager_Agent.h"
#include "Buffermanager.h"
#include "Socket_I_O_Buff.h"
#include "WriteAgent.h"
#include "ReadAgent.h"
#include "Epoll.h"

class D_Agent: public Agent
{
    public:
        D_Agent(int );
        ~D_Agent();
        class Buffermanager* Readbuff;
        class Buffermanager Readbuff_head;
        class Buffermanager Readbuff_data;
        class Socket_I_O_Buff Writebuff;
        class WriteAgent D_write;
        class ReadAgent D_read;
        struct mesg_head i_o_head;

        int read_stat;
        int read_len;
        int readagent();
        int writeagent();
        int getfd();
        int package_head_data();

};


#endif
