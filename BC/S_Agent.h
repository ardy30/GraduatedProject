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
#ifndef _S_AGENT_H_
#define _S_AGENT_H_
#include "head.h"
#include "Buffermanager.h"
#include "WriteAgent.h"
#include "ReadAgent.h"
#include "Epoll.h"
#include "BusinessController.h"

class S_Agent: public Agent
{
    public:
        S_Agent( Epoll*);
        ~S_Agent();
        class Buffermanager Readbuff;
        class Buffermanager Writebuff;
        class WriteAgent S_write;
        class ReadAgent S_read;

        struct mesg_head message_head;
        string load;

//        int error;
        int finish;
        //class BusinessController *BC;
        class Epoll *m_epoll;

        int setnonblocking(int);
        int connect_server(char*,int);
        int readagent();
        int writeagent();

        int getfd();

};


#endif
