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
#include "S_Manager_Agent.h"
#include "Buffermanager.h"
#include "WriteAgent.h"
#include "ReadAgent.h"
#include "Epoll.h"

class S_Agent: public Agent
{
    public:
        S_Agent( );
        ~S_Agent();
        class Buffermanager Readbuff;
        class Buffermanager Writebuff;
        class WriteAgent S_write;
        class ReadAgent S_read;

        int setnonblocking(int);
        int connect_server(char*);
        int readagent();
        int writeagent();

        int getfd();

};


#endif
