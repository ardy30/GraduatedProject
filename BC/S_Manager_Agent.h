/*
 * =====================================================================================
 *
 *       Filename:  S_Manager_Agent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/12 11:34:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _D_MANAGER_AGENT_H
#define _D_MANAGER_AGENT_H

#include "head.h"
#include "Buffermanager.h"
#include "S_Agent.h"

class S_Manager_Agent
{
    public:
        S_Manager_Agent();
        ~S_Manager_Agent();
        class S_Agent* s_agent;
        class Buffermanager MESGHEADbuff;
        class Buffermanager Databuff;
        struct mesg_head* i_o_head;

        class Buffermanager buff[DISK_BLOCK_NUMBER/2];

        int exec();
        int read_from_disk();
        int write_to_disk();
};

extern class S_Manager_Agent s_manager_agent;
#endif
