/*
 * =====================================================================================
 *
 *       Filename:  Agent.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/12 10:25:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yushiyao (), yushiyaogg@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#ifndef _AGENT_H_
#define _AGENT_H_
#include "head.h"
class Agent
{
    public:
        virtual int readagent(){return 0;}
        virtual int writeagent(){return 0;}
        virtual int getfd(){return -1;}
        int fd;
};
#endif
