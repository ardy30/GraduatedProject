/*
 * =====================================================================================
 *
 *       Filename:  Epoll.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年02月16日 15时48分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 *
 */
#include "Epoll.h"
#include "head.h"

Epoll::Epoll()
{
    nfd = -1;
    m_event = NULL;
    memset(&ev, 0 ,sizeof(epoll_event));
    //gettimeofday(&starttime,NULL);
    //gettimeofday(&endtime,NULL);
}
int Epoll::getfd() const
{
    return nfd;
}

int Epoll::epoll_init()
{
    if((nfd = epoll_create(MAXEPOLL)) < 0)
		return -1;
    m_event = new epoll_event[MAXEPOLL];
    memset(m_event, 0, sizeof(epoll_event) * MAXEPOLL);
    return 0;
}

int Epoll::epoll_registe(uint32_t e_event, Agent* agent)
{
    this->ev.data.ptr = agent;
    this->ev.events = e_event;
    int tempfd = agent->getfd();
    if(epoll_ctl(nfd, EPOLL_CTL_ADD,tempfd,&ev) < 0)
    {
        cout<<"epoll_ctl error\n"<<endl;
        return -1;
    }
    return 0;
}

int Epoll::epoll_delete( Agent* agent)
{
    ev.data.ptr = agent;
    int tempfd = agent->getfd();
    if(epoll_ctl(nfd,EPOLL_CTL_DEL,tempfd,&ev) < 0)
    {
        cout<<"epoll_ctl error\n"<<endl;
        return -1;
    }
    return 0;
}

int Epoll::epoll_modify(uint32_t e_event,Agent* agent)
{
    ev.data.ptr = agent;
    ev.events = e_event;
    int tempfd = agent->getfd();
    if(epoll_ctl(nfd, EPOLL_CTL_MOD,tempfd,&ev) < 0)
    {
        cout<<"epoll_ctl error\n"<<endl;
        return -1;
    }
    return 0;
}

int Epoll::epollwait()
{
    int numfd;
        if((numfd = epoll_wait(nfd,m_event,MAXEPOLL,-1)) < 0)
        {
            cout<<"epoll_wait error\n"<<endl;
            return -1;
        }
        for(int i = 0; i < numfd; i++)
        {
            Agent *agent = static_cast<Agent*>(m_event[i].data.ptr);
            if(m_event[i].events&(EPOLLERR|EPOLLHUP))
            {
              //  cout<<"epollerr or epollhup"<<endl;
                delete agent;
            }
            else if(m_event[i].events&EPOLLIN)
            {
                   /*  int mark;
                mark = (agent->userID) % 2;
                if(mark == 1)
                {
                    response ++;
                    if(response >= 10000)
                    {
                        gettimeofday(&endtime,NULL);
                        float num = response/(endtime.tv_sec - starttime.tv_sec +(endtime.tv_usec - starttime.tv_usec) * 0.000001);
                        cout<<"the number of response is :"<<num<<endl;
                        response = 0;
                        starttime = endtime;
                    }
                    
                }*/
                if(agent->readagent() < 0)
                    {
                       // cout<<"read error"<<endl;
                       // the value of read is 0,delete this agent
                    }
            }
            else if(m_event[i].events&EPOLLOUT)
            {
                if(agent->writeagent() < 0)
                {
                    cout<<"write error\n"<<endl;
                }
            }
        }

}

Epoll::~Epoll()
{
    close(nfd);
    delete []m_event;    
}

//class Epoll m_epoll;

