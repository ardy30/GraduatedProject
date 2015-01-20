/*
 * =====================================================================================
 *
 *       Filename:  Epoll.h
 *
 *    Description:  the head file of Epoll
 *
 *        Version:  1.0
 *        Created:  2012年02月16日 09时56分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef  _EPOLL_H
#define  _EPOLL_H
#include "head.h"
#include "Agent.h"
class Epoll
{
    public:
        int response;
        //struct timeval starttime;
        //struct timeval endtime;
        int epoll_init();
        int epoll_registe(uint32_t ev, Agent*);
        int epoll_delete( Agent*);
        int epoll_modify(uint32_t ev, Agent*);
        int epollwait();
        int getfd() const;
        ~Epoll();
        Epoll();
    private:
        int                      nfd;
        struct  epoll_event*      m_event;
        struct  epoll_event      ev;
};
extern class Epoll m_epoll;
#endif
