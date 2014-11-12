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

static void sighandler(int sig_no)
{
    exit(0);
}
 
int main(int argc, char **argv)
{
  /*  I_Listenagent* i_lisagent = new I_Listenagent();
    if((i_lisagent -> initialserver()) < 0) 
    {
        cerr<< "i_initialserver error"<<endl;
        delete i_lisagent;
        return -1;
    }*/
  /*    D_Listenagent* d_lisagent = new D_Listenagent() ;
    if((d_lisagent -> initialserver()) < 0)
    {
        cerr<< "d_initialserer error"<<endl;
        delete d_lisagent;
        return -1;
    }*/
    int fd;
    struct sockaddr_in servaddr;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(32600);
    if((fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {   
        cerr<<"socket error:"<<strerror(errno)<<"\n"<<endl;
        return -1; 
    }   
    if(bind(fd,(struct sockaddr *)&servaddr, sizeof(servaddr)) <0) 
    {   
        cerr<<"bind error:"<<strerror(errno)<<"\n"<<endl;
        return -1; 
    }   
    if(listen(fd,LISTENQ) < 0)
    {   
        cerr<<"listen error:"<<strerror(errno)<<"\n"<<endl;
        return -1; 
    }

    int connfd;
    int flag;
    int ret;
    socklen_t clilen;
    sockaddr_in cliaddr;
    clilen = sizeof(cliaddr);
    
    if((connfd = accept(fd, (SA *)&cliaddr,&clilen)) < 0)
    {
        cerr<<"accept error"<<strerror(errno)<<endl;
        return -1;
    }
    int n;
    if((flag = fcntl(connfd, F_GETFL, 0)) < 0)
    {   
        cerr<<"fcntl error:"<<"\n"<<endl;
        return -1; 
    }   
    if(fcntl(connfd,F_SETFL,flag|O_NONBLOCK) < 0)
     {   
        cerr<<"fcntl error:"<<"\n"<<endl;
        return -1; 
     }   
    while(1)
    { 
    struct mesg_head ptr;
    if((n = read(connfd, &ptr,16)) < 0)
    {   

    }   

    else if(n == 0)
    {   
        cout << "FIN"<< endl;
       // return READ_END;
    }
    else
    {
        if(ptr.NewOpcode == MAPOP)
        {
            sleep(5);
            ptr.NewOpcode = MAPOP_ACK;
            write(connfd,&ptr,16);
            cout << "MAPOP"<< endl;
        }
    }
    sleep(5);
    ptr.NewOpcode = HEARTBEAT;
    write(connfd,&ptr,16);
    cout << "heartbeat"<< endl;
       
}

  /*    if((m_epoll.epollwait()) < 0)
    {
      //  delete i_lisagent;
        delete d_lisagent;
        return -1;
    }*/
   // delete d_lisagent;
   // delete i_lisagent;
    return 0;
}
