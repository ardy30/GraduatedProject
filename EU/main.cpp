/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/12 10:40:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include "head.h"
#include "Epoll.h"
#include "I_Listenagent.h"
#include "EU_Listenagent.h"

static void sighandler(int sig_no)
{
    exit(0);
}
int main(int argc, char **argv)
{
    signal(SIGUSR1,sighandler);
    if((m_epoll.epoll_init()) < 0)
        return -1;
    I_Listenagent* i_lisagent = new I_Listenagent();
    if((i_lisagent -> initialserver()) < 0) 
    {
        cerr<< "i_initialserver error"<<endl;
        delete i_lisagent;
        return -1;
    }
    EU_Listenagent* eu_lisagent = new EU_Listenagent();
    if((eu_lisagent -> initialserver()) < 0) 
    {
        cerr<< "eu_initialserver error"<<endl;
        delete eu_lisagent;
        return -1;
    }
/*    D_Listenagent* d_lisagent = new D_Listenagent() ;
    if((d_lisagent -> initialserver()) < 0)
    {
        cerr<< "d_initialserver error"<<endl;
        delete d_lisagent;
        return -1;
    }*/

    if((m_epoll.epollwait()) < 0)
    {
        delete i_lisagent;
        delete eu_lisagent;
       // delete d_lisagent;
        return -1;
    }
   // delete d_lisagent;
    delete i_lisagent;
    delete eu_lisagent;
    return 0;
}
