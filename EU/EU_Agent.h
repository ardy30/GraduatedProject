/*
 * =====================================================================================
 *
 *       Filename:  S_Agent.h
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
#ifndef _EU_AGENT_H_
#define _EU_AGENT_H_
#include "head.h"
//#include "S_Manager_Agent.h"
#include "Buffermanager.h"
#include "WriteAgent.h"
#include "ReadAgent.h"
#include "Epoll.h"
#include "DataSet.h"

class EU_Agent: public Agent
{
    public:
        EU_Agent(int);
        EU_Agent();
        ~EU_Agent();
        class ReadAgent EU_read;
        class WriteAgent EU_write;
        class Socket_I_O_Buff Writebuff;
        class Buffermanager* Readbuff;
        class Buffermanager Readbuff_head;
        class Buffermanager Readbuff_data;
        struct mesg_head *Head;

        int read_len;
        int read_stat;

        int error;

        int readagent();
        int writeagent();
        int getfd();
        int exec();
        int package_head_data();
        int cmnd_exec();
        
        int connect_server(char*);
        int setnonblocking(int);


};


#endif
