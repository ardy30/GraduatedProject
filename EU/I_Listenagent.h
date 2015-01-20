/*
 * =====================================================================================
 *
 *       Filename:  Listenagent.h
 *
 *    Description:  the file is the head file of Listenagent.cpp
 *
 *        Version:  1.0
 *        Created:  2011年09月15日 10时04分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef  _I_LISTENAGENT_H
#define  _I_LISTENAGENT_H
#include "head.h"
#include "Epoll.h"
class I_Listenagent :public Agent
{
    public:
        I_Listenagent();
        int readagent();
        int writeagent(){return 0;}
        int initialserver();
        int getfd(){return fd;}
    private:
        int setnonblocking (int ) const;
        int m_port;
};
#endif
